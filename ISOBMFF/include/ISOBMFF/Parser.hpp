/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 DigiDNA - www.digidna.net
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      Parser.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_PARSER_HPP
#define ISOBMFF_PARSER_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <string>
#include <functional>
#include <memory>
#include <cstdint>
#include <ISOBMFF/Box.hpp>
#include <ISOBMFF/File.hpp>

namespace ISOBMFF
{
    /*!
     * @class       Parser
     * @abstract    ISO media file parser.
     */
    class ISOBMFF_EXPORT Parser: public XS::PIMPL::Object< Parser >
    {
        public:
            
            using XS::PIMPL::Object< Parser >::impl;
            
            /*!
             * @enum        StringType
             * @abstract    Possible types for strings in an ISO media file.
             * @discussion  ISO/IEC 14496-12 only specifies UTF-8 NULL
             *              terminated strings, but QuickTime actually uses
             *              Pascal strings.
             * @constant    NULLTerminated  UTF-8 NULL terminated strings.
             * @constant    Pascal          Pascal strings (length prefixed).
             */
            enum class StringType: int
            {
                NULLTerminated,
                Pascal
            };
            
            /*!
             * @enum        Options
             * @abstract    Parser options.
             * @constant    SkipMDATData    Do not keep data found in MDAT boxes.
             */
            enum class Options: uint64_t
            {
                SkipMDATData = 1 << 0
            };
            
            /*!
             * @function    Parser
             * @abstract    Default constructor.
             */
            Parser( void );
            
            /*!
             * @function    Parser
             * @abstract    Creates a parser for a file.
             * @param       path    The file's path.
             */
            Parser( const std::string & path );
            
            /*!
             * @function    Parser
             * @abstract    Creates a parser for data.
             * @param       data    The data bytes.
             */
            Parser( const std::vector< uint8_t > & data );
            
            /*!
             * @function    Parser
             * @abstract    Creates a parser for a stream.
             * @param       stream  The stream object.
             */
            Parser( BinaryStream & stream );
            
            /*!
             * @function    RegisterBox
             * @abstract    Registers a custom box type.
             * @param       type        The custom box type (four character string).
             * @param       createBox   A lambda returning a new box of the custom type.
             * @discussion  When encountering a box of the specified custom type,
             *              the parser will invoke the lambda to create a new
             *              object of the correct type.
             */
            void RegisterBox( const std::string & type, const std::function< std::shared_ptr< Box >( void ) > & createBox );
            
            /*!
             * @function    RegisterContainerBox
             * @abstract    Registers a custom box type as a container box.
             * @param       type    The custom box type (four character string).
             */
            void RegisterContainerBox( const std::string & type );
            
            /*!
             * @function    CreateBox
             * @abstract    Creates a new box for a specific type.
             * @param       type    The box type (four character string).
             * @result      A new box.
             */
            std::shared_ptr< Box > CreateBox( const std::string & type ) const;
            
            /*!
             * @function    Parse
             * @abstract    Parses a file.
             * @discussion  This will discard any previously parsed file.
             * @param       path    The file's path.
             */
            void Parse( const std::string & path ) ISOBMFF_NOEXCEPT( false );
            
            /*!
             * @function    Parse
             * @abstract    Parses data.
             * @discussion  This will discard any previously parsed file/data.
             * @param       data    The data bytes.
             */
            void Parse( const std::vector< uint8_t > & data ) ISOBMFF_NOEXCEPT( false );
            
            /*!
             * @function    Parse
             * @abstract    Parses data from a stream.
             * @discussion  This will discard any previously parsed file/data.
             * @param       stream  The stream object.
             */
            void Parse( BinaryStream & stream ) ISOBMFF_NOEXCEPT( false );
            
            /*!
             * @function    GetFile
             * @abstract    Upon successfull parsing, gets the file object.
             * @result      The file object, or nullptr.
             */
            std::shared_ptr< File > GetFile( void ) const;
            
            /*!
             * @function    GetPreferredStringType
             * @abstract    Gets the preferred string type used in the parser.
             * @result      The preferred string type.
             * @see         StringType
             */
            StringType GetPreferredStringType( void ) const;
            
            /*!
             * @function    SetPreferredStringType
             * @abstract    Sets the preferred string type to use in the parser.
             * @param       value   The preferred string type.
             * @see         StringType
             */
            void SetPreferredStringType( StringType value );
            
            /*!
             * @function    GetOptions
             * @abstract    Gets the parser options.
             * @result      The parser options.
             * @see         Options
             */
            uint64_t GetOptions( void ) const;
            
            /*!
             * @function    SetOptions
             * @abstract    Sets the parser options.
             * @param       value   The parser options.
             * @see         Options
             */
            void SetOptions( uint64_t value );
            
            /*!
             * @function    AddOption
             * @abstract    Sets a specific parser option.
             * @param       option  The option to set/add.
             * @see         Options
             */
            void AddOption( Options option );
            
            /*!
             * @function    RemoveOption
             * @abstract    Removes a specific parser option.
             * @param       option  The option to remove.
             * @see         Options
             */
            void RemoveOption( Options option );
            
            /*!
             * @function    HasOption
             * @abstract    Checks if a specific parser option is set.
             * @param       option  The option to check for.
             * @result      true if the option is set, otherwise false.
             * @see         Options
             */
            bool HasOption( Options option );
            
            /*!
             * @function    GetInfo
             * @abstract    Gets an info value in the parser.
             * @param       key The info key.
             * @result      The value for the info key, or nullptr.
             * @see         SetInfo
             */
            const void * GetInfo( const std::string & key );
            
            /*!
             * @function    SetInfo
             * @abstract    Sets an info value in the parser.
             * @discussion  This method can be used to store any kind of
             *              contextual information that may be useful while
             *              parsing.
             * @param       key     The info key.
             * @param       value   The info value.
             * @see         GetInfo
             */
            void SetInfo( const std::string & key, void * value );
    };
}

#endif /* ISOBMFF_PARSER_HPP */
