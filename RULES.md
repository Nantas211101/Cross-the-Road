# Coding rules

1. `using namespace std` is not allowed.
2. All code must use **inline braces**.
3. [Variables must have sensible names](https://www.youtube.com/watch?v=-J3wNP6u5YU), however, there are exceptions on variables in `for-loop` and ubiquitious names, such as tmp, cnt, cur.
4. [Don't comment too much](https://www.youtube.com/watch?v=Bf7vDBBOBUA), try to write codes that make sense instead.
5. Use [#pragma once](https://en.wikipedia.org/wiki/Pragma_once) instead of [`#include` guard](https://en.wikipedia.org/wiki/Include_guard) for **all header files**. In terms of the definition of `class`, please do not implement functions in header file, except for `the constructor and destructor`.
6. Remember to create **include** folder, **res** folder and **src** folder, **template** folder which:
    + `include` folder will hold all the **.hpp** file
    + `res` folder will hold all the **resource** (.png, font, ...)
    + `src` folder will hold all the **.cpp** file
    + `template` folder will holl all the **.inl** file
---

# Github rules

1. Most branches should be named like this: **task-name-with-hyphen**. For example, the branch for the task **Change the definition** should be named **change-the-definition**.
2. **Please, for the sake of reading, write sensible commit message.**
3. Please resolve all errors and warnings before commiting.
4. Before merging the branch, a pull request for the branch must be opened and all changes in it must be approved **by at least 2 people**.
   - A pull request can only be opened when **the code is ready for review**.
   - It can have the same name as the branch for simplicity's sake.
   - It should have a description about **what have been done in the code** and **how to use the new feature** to make review easier.
   - It should be linked to the corresponding Trello task to make it easier to find.


## Note

You may seem this Coding rules as a "should" but I recommend you to consider this **more** than just a "should". It 's likely to **between "should" and "must"**.

##### Note: More rules might be added later on.

