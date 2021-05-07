### Code convention 

### Naming

- Namespaces: *snake_case*
- Classes: *snake_case*
- Class members: *`m_` prefixed snake_case*
- Class member getters: *class_member name without the `m_` prefix*
- Interfaces => *`I_` prefixed snake_case*
- Files
    - _source_: `snake_case.cc`
    - _header_: `snake_case.hh`
        
-------

### Structure
- Each directory is compiled as a separate library which gets included
from higher level client code

-------

### Functions

*Empty for now :(*

-------
        
### Classes
- Class definitions follow this structure:
        
    ```c++
  
    /**
     * Brief description
     * ...
     */
    class example_class {
    private:
        /// Info about `m_field1`
        type m_field1;
  
        /// Info about `m_field2`
        type m_field2;
        
    public:
        ///
        /// Constructors and destructors
        ///
        
    public:
        ///
        /// API
        ///
  
        /*
         * @brief  ... 
         * @note   ...  
         * @param  [in|out] param   ...
         * @return ...
         */
        type do_something1(type param);
  
        /*
         * @brief  ... 
         * @note   ...  
         * @param  [in|out] param1   ...
         * @param  [in|out] param2   ...
         * @return ...
         */
        type do_something2(type param1, type param2);
        
    public:
        ///
        /// Getters (optionally also setters)
        ///
        
        type field1() const noexcept {
            return m_field1;
        }
        
        ...
    };
    ```
  
 ----------------
 ### Includes
 - Include order is the following:
    1. Standard library
    2. Other external libraries
    3. Local libraries
    4. Local headers
 - **Additional:** New line between each category may help :)
    
    Example
    ```c++
   #include <algorithm>

   #include <boost/...>

   #include <local_lib/...>

   #include <blah.hh>
   
    ```
   
-----------------
### Misc
- Prefer initializing with `{}` over `()`
    + Example
    ```cpp
    blah b{blah_blah};
    ```
  