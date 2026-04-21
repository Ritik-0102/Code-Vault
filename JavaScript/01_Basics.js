// This is a simple JavaScript file that prints "Hello World!" to the console.
console.log("Hello World!");

// JavaScript is a Dynamically typed language, which means you don't need to declare the type of a variable.
Name = "Ritik";
age= 21;
isTrue = true;

// This is an alert box that will display a message to the user.
alert("Hello, this is an alert!");

// Prompt is used to take input from the user.
const userName = prompt("Please enter your name:");
console.log("Hello, " + userName + "!");



// Data types in JavaScript :-

// Primitive Data Types :-
// Number, String, Boolean, Undefined, Null, Symbol, BigInt

console.log(typeof Name); // Output: string
console.log(typeof age); // Output: number
console.log(typeof isTrue); // Output: boolean
console.log(typeof undefined); // Output: undefined
console.log(typeof null); // Output: object
console.log(typeof Symbol()); // Output: symbol
console.log(typeof BigInt(100)); // Output: bigint

// Object Data Types :-
// Object, Array, Function, Date, RegExp, Error, Map, WeakMap, Set, WeakSet

const person = {
    name: "Ritik",
    age: 21,
    isStudent: true,
    hobbies: ["Reading", "Coding", "Sports"],
    address: {
        city: "New Delhi",
        country: "India",
        pincode: 110001
    }
};

console.log(person); // Output: { name: 'Ritik', age: 21, isStudent: true, hobbies: [ 'Reading', 'Coding', 'Sports' ], address: { city: 'New Delhi', country: 'India', pincode: 110001 } }
console.log(typeof person); // Output: object



// Operators in JavaScript :-

// Arithmetic Operators
console.log(1 + 1); // Output: 2
console.log(5 - 3); // Output: 2
console.log(4 * 5); // Output: 20
console.log(10 / 2); // Output: 5
console.log(10 % 3); // Output: 1


// Assignment Operators
let x = 5;
x += 3; // Equivalent to x = x + 3;
console.log(x); // Output: 8

let y = 5;
y -= 3; // Equivalent to y = y - 3;
console.log(y); // Output: 2

let z = 5;
z *= 3; // Equivalent to z = z * 3;
console.log(z); // Output: 15

let a = 5;
a /= 3; // Equivalent to a = a / 3;
console.log(a); // Output: 1.6666666666666667

let b = 5;
b %= 3; // Equivalent to b = b % 3;
console.log(b); // Output: 2


// Comparison Operators
console.log(5 > 3); // Output: true
console.log(5 < 3); // Output: false
console.log(5 >= 3); // Output: true
console.log(5 <= 3); // Output: false
console.log(5 == "5"); // Output: true (loose equality)
console.log(5 === "5"); // Output: false (strict equality)


// Equality Operators
console.log(5 == 5); // Output: true
console.log(5 === 5); // Output: true
console.log(5 != 5); // Output: false
console.log(5 !== 5); // Output: false


// Logical Operators
console.log(true && false); // Output: false
console.log(true || false); // Output: true


// Bitwise Operators
console.log(~5); // Output: -6
// Example: 5 in binary is 0101, so ~5 is 1010 in binary, which is -6 in decimal.
console.log(5 & 3); // Output: 1
// Example: 5 in binary is 0101 and 3 in binary is 0011, so 5 & 3 is 0001 in binary, which is 1 in decimal.
console.log(5 | 3); // Output: 7  
// Example: 5 in binary is 0101 and 3 in binary is 0011, so 5 | 3 is 0111 in binary, which is 7 in decimal.
console.log(5 ^ 3); // Output: 6
// Example: 5 in binary is 0101 and 3 in binary is 0011, so 5 ^ 3 is 0110 in binary, which is 6 in decimal.



// Assignment Operators
x = 5;
x <<= 3; // Equivalent to x = x << 3;
console.log(x); // Output: 40

let y = 5;
y >>= 3; // Equivalent to y = y >> 3;
console.log(y); // Output: 1

let z = 5;
z >>>= 3; // Equivalent to z = z >>> 3;
console.log(z); // Output: 1

// Increment and Decrement Operators
let a = 5;
a++; // Equivalent to a = a + 1;
console.log(a); // Output: 6

let b = 5;
b--; // Equivalent to b = b - 1;
console.log(b); // Output: 4

// Ternary Operator
const isStudent = true;
console.log(isStudent ? "Yes" : "No"); // Output: Yes

