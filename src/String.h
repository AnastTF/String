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

    class Iterator{
    public:
        Iterator(char* ptr);
        virtual ~Iterator();
        Iterator& operator++();

        Iterator operator++(int);
        bool operator==(const Iterator& iter) const;
        bool operator!=(const Iterator& iter) const;

    protected:
        char* mPtr;
    };

    class StringIterator: public Iterator{
    public:
        StringIterator( char* ptr );
        ~StringIterator();

        char& operator*();
    };

    class ConstStringIterator: public Iterator{
    public:
        ConstStringIterator( char* ptr );
        ~ConstStringIterator();

        const char& operator*() const;
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
    char&                   operator[]( const int indx );
    const char&             operator[]( const int indx ) const ;
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

    StringIterator          begin();
    StringIterator          end();
    ConstStringIterator     cbegin() const;
    ConstStringIterator     cend() const;

    String                  toLower() const;
private:
    void                    resize( size_t new_size );

};
#endif