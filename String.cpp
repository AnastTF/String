#include "String.h"
#include <cstring>
#include <exception>

String::String(): length( 0 ), capacity( START_LENGTH_ARRAY )
{
    str = new char[ capacity ];
}

String::String( const String& other ): length( other.length ), capacity( other.capacity )
{
    str = new char[ capacity ];
    strcpy( str, other.str );
}

String::String( const char* other )
{
    length = strlen( other );
    capacity = length + 1;
    str = new char[ capacity ];
    strcpy( str, other );
}

String::String( String&& move_other ) noexcept: length( move_other.length ), capacity( move_other.capacity )
{
    str = move_other.str;
    move_other.length = 0;
    move_other.capacity = 0;
    move_other.str = nullptr;
}

String::~String()
{
    delete[] str;
}

size_t String::size() const noexcept
{
    return length;
}

size_t String::get_capacity() const noexcept
{
    return capacity;
}

void String::clear() noexcept
{
    length = 0;
    capacity = 0;
    delete[] str;
    str = nullptr;
}

bool String::empty() const noexcept
{
    return !( length );
}

const char* String::data() const noexcept
{
    return str;
}

String& String::operator =( const String& other )
{
    if( this == &other )
        return *this;
    
    length = other.length;
    capacity = other.capacity;
    delete[] str;
    str = new char[ capacity ];
    strcpy( str, other.str );
    
    return *this;
}

String& String::operator =( String&& other ) noexcept
{
    if( this == &other )
        return *this;
    
    delete[] str;
    length = other.length;
    capacity = other.capacity;
    str = other.str;
    other.str = nullptr;
    other.length = 0;
    other.capacity = 0;

    return *this;
}

void String::push_back( const char c )
{
    if( length >= capacity )
        resize( capacity * RESIZE_FACTOR );
    
    if( length < capacity )
        str[ length++ ] = c;
}

void String::resize( size_t new_size )
{
    if( new_size <= capacity )
        return;
    
    while ( capacity < new_size )
    {
        capacity *= RESIZE_FACTOR;
        
        if(capacity >= MAX_LENGTH_ARRAY){
            capacity = MAX_LENGTH_ARRAY;
            break;
        }
    }

    char* p = new char[ capacity ];
    strcpy( p, str );
    delete[] str;
    str = p;    
}

void String::pop_back()
{
    if( length <= 0 )
        return;

    if( length > 0 )
        --length;
}

String& String::append( const String& other )
{
    if( this == &other ){
        String new_str( other );
        new_str.append( other.str );

        *this = new_str;
    }

    else{
        resize( length + other.length );

        for( size_t i = 0; i != other.length; ++i )
            str[length++] = other.str[i];
    }

    return *this;
}

String& String::append( const char* s )
{
    if( s == nullptr )
        throw std::logic_error( "Invalid argument append" );
    
    resize(length + strlen( s ));
    
    for( size_t i = 0; i != strlen( s ); ++i )
        str[length++] = s[i]; 
    
    return *this;
}

String::Item String::operator[]( int indx )
{
    return String::Item( this, indx );
}

String::Item::operator char() const
{
    if( indx > current->length || indx < 0 )
        throw std::out_of_range( "String: at() out of range" );
    
    return current->str[ indx ];
}

char String::Item::operator =( char ch ) const
{
    if( indx >= MAX_LENGTH_ARRAY || indx < 0 )
        return ch; 
 
    if( indx >= current->capacity ) 
        current->resize( indx+1 );
 
    for( int i = current->length; i < indx; ++i )
        current->str[ i ] = '\0';   
 
    if( indx >= current->length )
        current->length = indx + 1; 
 
    current->str[ indx ] = ch;
    
    return ch;
}

char& String::at( const size_t pos ) const
{
    if( pos > length )
        throw std::out_of_range( "String: at() out of range" );
    
    return str[ pos ];
}


String& String::operator +=( const String& other )
{
    return append( other );
}

String& String::operator +=( const char* other )
{
    return append( other );
}

String& String::operator +=( const char ch )
{
    push_back(ch);
    return *this;
}

const String operator +( const String& left, const String& right )
{
    String str_result ( left );
    
    str_result.append( right );
    
    return str_result;
}

const String operator +( const String& left, const char* right )
{
    return left + String( right );
}

const String operator +( const char* left, const String& right )
{
    return String( left ) + right;
}

bool String::operator <( const String& other ) const
{
    auto cmp_len = std::min( length, other.length );
    
    return ( strncmp( str, other.str, cmp_len ) < 0 );
}

bool String::operator >( const String& other ) const
{
    return !( *this < other );
}

bool operator ==( const String& left, const String& right )
{
    auto left_sz = left.length;
    auto right_sz = right.length;
    
    if( left_sz == 0 && right_sz == 0 )
        return true;
    
    if( left.str == nullptr || right.str == nullptr )
        return false;
    
    return !( strncmp( left.str, right.str, std::min(left_sz, right_sz) ) );
}

bool operator ==( const String& left, const char* right )
{
    return left == String( right );
}

bool operator !=( const String& left, const String& right )
{
    return !( left == right );
}

std::ostream& operator <<( std::ostream& os, const String& other )
{
    os << other.str;
    return os;
}

std::istream& operator >>( std::istream& is, String& other )
{
    char temp[ 80 ];
    is.get( temp, 80 );

    if ( is )
        other = temp;

    while ( is && is.get() != '\n' )
        continue;

    return is;
}

String String::toLower() const
{
    if( !str )
        return String();
    
    String str_to_lower;

    for( auto iter = begin(); !iter->IsEnd(); iter->next() )
        str_to_lower += std::tolower(iter->CurrentItem());
    
    return str_to_lower;
}

String::StringIterator::StringIterator( const String* vl_ptr ) : ptr( vl_ptr )
{}

void String::StringIterator::first()  
{ 
    indx = 0; 
}

void String::StringIterator::next()  
{ 
    indx++; 
}

bool String::StringIterator::IsEnd() const  
{ 
    return indx >= ptr->size(); 
}

char String::StringIterator::CurrentItem() const 
{
    if( IsEnd() )
        throw std::out_of_range( "String: at() out of range" );
    return ptr->Get( indx );
}

String::StringIterator* String::begin() const noexcept
{
    return new String::StringIterator( this );
}

const char& String::Get( const size_t indx ) const
{
    return at( indx );
}
