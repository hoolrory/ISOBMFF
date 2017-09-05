/*******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
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
 * @file        Box.cpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/Box.hpp>

template<>
class XS::PIMPL::Object< IBMFF::Box >::IMPL
{
    public:
        
        IMPL( const std::string & name = "????" );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string _name;
};

#define XS_PIMPL_CLASS IBMFF::Box
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    Box::Box( const std::string & name ): XS::PIMPL::Object< Box >( name )
    {}
    
    std::string Box::GetName( void ) const
    {
        return this->impl->_name;
    }
    
    void Box::ReadData( const Parser & parser, BinaryStream & stream )
    {
        ( void )parser;
        ( void )stream;
    }
    
    void Box::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( indentLevel * 4, ' ' );
        
        os << i << "[ " << this->GetName() << " ]";
    }
    
    std::ostream & operator << ( std::ostream & os, const Box & box )
    {
        box.WriteDescription( os, 0 );
        
        return os;
    }
}

XS::PIMPL::Object< IBMFF::Box >::IMPL::IMPL( const std::string & name ):
    _name( name )
{}

XS::PIMPL::Object< IBMFF::Box >::IMPL::IMPL( const IMPL & o ):
    _name( o._name )
{}

XS::PIMPL::Object< IBMFF::Box >::IMPL::~IMPL( void )
{}