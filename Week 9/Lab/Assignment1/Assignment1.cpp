#include <string.h>
#include <iostream>
using namespace std;

void DisplayBits(char ch, int value);  // output value in binary
void ToUpper(char name[]);             // convert using AND(&)
void ToLower(char name[]);             // convert using OR(|)

int main() {
    int a, b, c, d;
    const int c255 = 255, c128 = 128;
    char name[5] = "COSC";
    char number[5] = "3306";

    cout << " Input two integers to be altered.\n";
    cin >> c >> d;
    a = c;
    b = d;
    cout << "Before changes we have:" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c << 2;
    b = d << 2;
    cout << "Use << to left shift 2:" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c >> 3;
    b = d >> 3;
    cout << "Use >>   right shift 3:" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c;
    b = d;
    a &= c255;
    b &= c255;
    cout << "AND (&) each with const 255 "
         << "(00000000 11111111):" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c;
    b = d;
    a &= c128;
    b &= c128;
    cout << "AND (&) each with 128 "
         << "(00000000 10000000):" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c | c255;
    b = d | c255;
    cout << "OR (|) each with 255 (00000000 11111111):" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c | c128;
    b = d | c128;
    cout << "OR (|) each with 128 (00000000 10000000):" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c;
    b = d;
    a ^= c255;
    b ^= c255;
    cout << "XOR (^) each with 255 (00000000 11111111):" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = c;
    b = d;
    a ^= c128;
    b ^= c128;
    cout << "XOR (^) each with 128 (00000000 10000000):" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a = ~c;
    b = ~d;
    cout << "ONES COMPLEMENT (~) of each:" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    a++;
    b++;
    cout << "Then add 1 to each to negate:" << endl;
    DisplayBits('a', a);
    DisplayBits('b', b);
    cout << endl;

    // 'A' is 65 or 0100 0001 in binary ( 64 + 1 )
    // 'a' is 97 or 0110 0001 in binary ( 64 + 32 + 1 )

    // The difference between an upper and lower case letter is 32.
    // In a binary number all values are powers of 2. You can see the bit
    // representing the 32's place is the 6th from the right. Thus the
    // conversion between cases is just a matter of changing one bit.

    cout << "Before conversion, name is             :" << name << endl;
    ToUpper(name);
    cout << "After converting to upper case using AND(&) :" << name << endl;
    ToLower(name);
    cout << "After converting to lower case using OR(|)  :" << name << endl;
    cout << endl;

    // While all lower case letters have a 1 in the 32 place, not
    // everything with this 1 is a lower case letter. For example,
    // the digits '0'..'9' have ASCII values 48..57. As 48 is 32 + 16,
    // the ToLower function makes no change. The ToUpper function
    // removes the 32 leaving ASCII values 0..9. As 0..31 represent
    // unprintable characters, ToUpper prints nothing visible.

    cout << "Before attempting conversion, number is:" << number << endl;
    ToUpper(number);
    cout << "After converting to upper case using AND(&) :" << number << endl;
    ToLower(number);
    cout << "After converting to lower case using OR(|)  :" << number << endl;

    return 1;
}
//////////////////////////////////////////////////////////////////////////

void DisplayBits(char ch, int value) {
    const int SHIFT = 8 * sizeof(int) - 1;
    const int MASK = 1 << SHIFT;

    cout << ch << " = " << value << " = ";

    // TODO: Implement the rest of the function that prints the
    // bits of a function from most-significant to least-significant
}

void ToLower(char name[]) {
    for (int i = 0; i < int(strlen(name)); i++) {
        // TODO: You know that the input is a character array containing letters (not numbers).
        // We want you to convert each character to its lowercase form
        // If it is already lower case keep it like that (i.e., A->a, a->a, B->b , etc..)
    }
}

void ToUpper(char name[]) {
    // TODO: We want a mask that will force the 32 bit to 0. If we could assume
    // we have a upper case letter, we could just subtract 32. As a bitwise
    // operation it makes sense to AND with the character whose value
    // all ones except the 32 bit. Rather than compute this value
    // numerically, just take the one's complement of 32.
}
