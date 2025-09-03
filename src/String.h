#ifndef __STRING_H_
#define __STRING_H_
#include <iostream>

class String{
    
    enum {
        /// init length of string
        START_LENGTH_ARRAY  =   8,
        /// resize factor is in order to increase capacity of string
        RESIZE_FACTOR       =   2,    
        /// max length of string  
        MAX_LENGTH_ARRAY    =   1000,  
    };

    char*                   str         {nullptr};
    size_t                  length      {0};
    size_t                  capacity    {0};
    
    class Item{ 
        String*             current     {nullptr};
        int                 indx        {-1};
    public:
                            Item( String* obj, int indx ) : current( obj ), indx( indx )                {}
                            operator char() const;
                            char operator =( char ch ) const;
    };
public:
                            String();
                            String( const String& other );
                            String( const char* other );
                            String( String&& move_other ) noexcept;
                            ~String();

    size_t                  size() const noexcept;
    size_t                  get_capacity() const noexcept;
    void                    clear() noexcept;
    bool                    empty() const noexcept;
    const char*             data() const noexcept;

    String&                 operator =( const String& other );
    String&                 operator =( String&& other ) noexcept;

    void                    push_back( const char c );
    void                    pop_back();
    String&                 append( const String& other );
    String&                 append( const char* s );
    Item                    operator[]( int indx );
    char&                   at( const size_t pos ) const;

    String&                 operator +=( const String& other );
    String&                 operator +=( const char* other );
    String&                 operator +=( const char ch );

    friend const String     operator +( const String& left, const String& right );
    friend const String     operator +( const String& left, const char* right );
    friend const String     operator +( const char* left, const String& right );

    bool                    operator <( const String& other ) const;
    bool                    operator >( const String& other ) const;
    friend bool             operator ==( const String& left, const String& right );
    friend bool             operator ==( const String& left, const char* right );
    friend bool             operator !=( const String& left, const String& right );

    friend std::ostream&    operator <<( std::ostream& os, const String& other );
    friend std::istream&    operator >>( std::istream& is, String& other );
    String                  toLower() const;
private:
    void                    resize( size_t new_size );
private:
    class StringIterator{
        unsigned            indx        {0};
        const String*       ptr;
    public:
                            StringIterator( const String* vl_ptr );
        void                first();
        void                next();
        bool                IsEnd() const;
        char                CurrentItem() const;
        };
        
public:
    StringIterator*         begin() const noexcept;
    const char&             Get(const size_t indx) const;
};
#endif