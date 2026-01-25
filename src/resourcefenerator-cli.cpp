/*
 * MIT License
 *
 * Copyright (c) 2026 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file resourcefenerator-cli.cpp
 * @brief Tool to embed binary resources as C++ byte arrays
 * @details Converts files to C++ source files with byte array data
 *
 * Usage: resourcefenerator-cli <input_file> <output_cpp> <namespace>
 */

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

std::string makeIdentifier( const std::string& str )
{
    std::string result;
    result.reserve( str.length() );

    for( size_t i = 0; i < str.length(); ++i )
    {
        char c = str[i];
        if( std::isalnum( static_cast<unsigned char>( c ) ) )
        {
            result += c;
        }
        else
        {
            result += '_';
        }
    }

    if( !result.empty() && std::isdigit( static_cast<unsigned char>( result[0] ) ) )
    {
        result = "_" + result;
    }

    return result.empty() ? "resource" : result;
}

bool isValidIdentifier( const std::string& id )
{
    if( id.empty() )
    {
        return false;
    }

    if( !std::isalpha( static_cast<unsigned char>( id[0] ) ) && id[0] != '_' )
    {
        return false;
    }

    for( size_t i = 1; i < id.length(); ++i )
    {
        if( !std::isalnum( static_cast<unsigned char>( id[i] ) ) && id[i] != '_' )
        {
            return false;
        }
    }

    return true;
}

bool isValidNamespace( const std::string& ns )
{
    if( ns.empty() )
    {
        return false;
    }

    size_t pos = 0;
    while( pos < ns.length() )
    {
        size_t nextColon = ns.find( "::", pos );
        std::string part = ( nextColon == std::string::npos ) ? ns.substr( pos ) : ns.substr( pos, nextColon - pos );

        if( !isValidIdentifier( part ) )
        {
            return false;
        }

        if( nextColon == std::string::npos )
        {
            break;
        }
        pos = nextColon + 2;
    }

    return true;
}

std::string escapeString( const std::string& str )
{
    std::string result;
    result.reserve( str.length() );

    for( char c : str )
    {
        switch( c )
        {
            case '\\':
                result += "\\\\";
                break;
            case '"':
                result += "\\\"";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            default:
                result += c;
                break;
        }
    }

    return result;
}

std::filesystem::path validatePath( const std::string& path, const std::string& pathType )
{
    try
    {
        return std::filesystem::weakly_canonical( path );
    }
    catch( const std::filesystem::filesystem_error& e )
    {
        std::cerr << "Error: Invalid " << pathType << " path: " << e.what() << "\n";
        return {};
    }
}

std::vector<uint8_t> readBinaryFile( const std::filesystem::path& path )
{
    std::ifstream input( path, std::ios::binary );
    if( !input )
    {
        std::cerr << "Error: Cannot open input file: " << path << "\n";
        return {};
    }

    std::vector<uint8_t> data( ( std::istreambuf_iterator<char>( input ) ), std::istreambuf_iterator<char>() );
    input.close();
    return data;
}

void writeByteArray( std::ofstream& output, const std::string& identifier, const std::vector<uint8_t>& data )
{
    if( data.empty() )
    {
        output << "    extern const uint8_t " << identifier << "_data[1] = { 0 };\n\n";
    }
    else
    {
        output << "    extern const uint8_t " << identifier << "_data[] = {\n";
        for( size_t i = 0; i < data.size(); ++i )
        {
            if( i % 16 == 0 )
            {
                output << "        ";
            }
            output << "0x" << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast<int>( data[i] );
            if( i + 1 < data.size() )
            {
                output << ",";
            }
            if( ( i + 1 ) % 16 == 0 || i + 1 == data.size() )
            {
                output << "\n";
            }
            else
            {
                output << " ";
            }
        }
        output << "    };\n\n";
    }
}

bool generateCppFile(
    const std::filesystem::path& outPath,
    const std::string& identifier,
    const std::string& filename,
    const std::string& ns,
    const std::vector<uint8_t>& data )
{
    std::ofstream output( outPath );
    if( !output )
    {
        std::cerr << "Error: Cannot create output file: " << outPath << "\n";
        return false;
    }

    const std::string escapedFilename = escapeString( filename );

    output << "// Auto-generated embedded resource from: " << filename << "\n\n";
    output << "#include <cstdint>\n";
    output << "#include <cstddef>\n\n";
    output << "namespace " << ns << "\n{\n";

    writeByteArray( output, identifier, data );

    output << "    extern const size_t " << identifier << "_size = " << std::dec << data.size() << ";\n\n";

    output << "    extern const char " << identifier << "_name[] = \"" << escapedFilename << "\";\n";

    output << "} // namespace " << ns << "\n";
    output.close();

    return true;
}

/**
 * @brief Main entry point for the resource generator tool
 *
 * @details This tool converts binary files into C++ source files containing
 *          byte arrays. The generated code is placed in a specified namespace.
 *          The identifier is automatically derived from the input path, but
 *          the resource name can be explicitly specified.
 *
 * @param argc Argument count (must be 4 or 5)
 * @param argv Command-line arguments:
 *             [1] input_file   - Path to the binary file to embed
 *             [2] output_cpp   - Path for the generated .cpp file
 *             [3] namespace    - C++ namespace for the generated code
 *             [4] resource_name (optional) - Name for the resource (defaults to filename)
 *
 * @return 0 on success, 1 on error
 *
 * Generated code structure:
 * - {identifier}_data: const uint8_t array containing the binary data
 * - {identifier}_size: const size_t containing the data size
 * - {identifier}_name: const char array containing the resource name
 */
int main( int argc, char* argv[] )
{
    if( argc != 4 && argc != 5 )
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_cpp> <namespace> [resource_name]\n";
        return 1;
    }

    const std::string inputFile = argv[1];
    const std::string outputCpp = argv[2];
    const std::string ns = argv[3];

    if( !isValidNamespace( ns ) )
    {
        std::cerr << "Error: Invalid C++ namespace: " << ns << "\n";
        std::cerr << "Namespace must be valid C++ identifier(s), optionally separated by '::'.\n";
        return 1;
    }

    const auto inPath = validatePath( inputFile, "input" );
    if( inPath.empty() )
    {
        return 1;
    }

    const auto outPath = validatePath( outputCpp, "output" );
    if( outPath.empty() )
    {
        return 1;
    }

    // Use provided resource name or default to filename
    const std::string resourceName = ( argc == 5 ) ? argv[4] : inPath.filename().string();
    const std::string identifier = makeIdentifier( resourceName );

    if( !isValidIdentifier( identifier ) )
    {
        std::cerr << "Error: Could not generate valid C++ identifier from resource name: " << resourceName << "\n";
        return 1;
    }

    const auto data = readBinaryFile( inPath );
    if( data.empty() && !std::filesystem::exists( inPath ) )
    {
        return 1;
    }

    if( !generateCppFile( outPath, identifier, resourceName, ns, data ) )
    {
        return 1;
    }

    std::cout << "Generated: " << outPath << " (" << data.size() << " bytes)\n";
    return 0;
}
