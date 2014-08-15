Description of the examples
---------------------------

1) minimal

The minimal example demonstrates how libunittest can be used to assemble the 
smallest test project imaginable. This example uses the macro shortcut TEST.

2) collection

The collection example demonstrates how to assemble a test project using
the macro shortcuts COLLECTION, TEST, and TEST_FIXTURE. This an efficient
way of writing unit tests quickly. Perfect for TDD!

3) random

The random example demonstrates, on the one hand, how to apply the macro
shortcut TEST in a larger test project and, on the other hand, how to 
generate random values and containers with libunittest.

4) flexible

The flexible example demonstrates how to use libunittest in the most flexible
way possible. It shows how to assemble test classes with and without test 
contexts. This kind of test project compiles significantly faster than when
using the macros TEST and TEST_FIXTURE. Due to flexibility and compile
time reasons it is recommended to use the testing style demonstrated in this
example for larger test projects. 

5) templates

The templates example demonstrates how two define templated tests.
Tests that use the macro shortcuts TEST_TPL and TEST_TPL_FIXTURE support
up to three types: Type1, Type2, Type3. Defining templated tests using an
explicit test class is also demonstrated.
