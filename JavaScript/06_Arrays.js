// Arrays are a special type of objects in JavaScript that can hold multiple values. They can contain elements of any type, including other arrays.
// They are mutable, which means that you can change the contents of an array after it has been created.

let fruits = ["Apple", "Banana", "Cherry"];
let info = ["rahul", 86, "Delhi" ];

let array = [1, 2, 3, 4, 5];


array[0] = 10;

console.log(array);

for(let ele of array) {
    console.log(ele);
}

// Array Methods in JS :-

// push() - Adds one or more elements to the end of an array and returns the new length of the array
fruits.push("Orange");
console.log(fruits); // Output: ["Apple", "Banana", "Cherry", "Orange"]

// pop() - Removes the last element from an array and returns that element
fruits.pop();
console.log(fruits); // Output: ["Apple", "Banana", "Cherry"]

// shift() - Removes the first element from an array and returns that element
fruits.shift();
console.log(fruits); // Output: ["Banana", "Cherry"]

// unshift() - Adds one or more elements to the beginning of an array and returns the new length of the array
fruits.unshift("Mango");
console.log(fruits); // Output: ["Mango", "Banana", "Cherry"]

// slice() - Returns a shallow copy of a portion of an array into a new array object
let slicedFruits = fruits.slice(1, 3);
console.log(slicedFruits); // Output: ["Banana", "Cherry"]

// splice() - Adds/Removes elements from an array and returns the deleted elements
slicedFruits = fruits.splice(1, 2);
console.log(slicedFruits); // Output: ["Banana", "Cherry"]
console.log(fruits); // Output: ["Apple", "Mango"]

// concat() - Joins two or more arrays and returns a copy of the joined arrays
let newArray = fruits.concat(info);
console.log(newArray); // Output: ["Apple", "Banana", "Cherry", "rahul", 86, "Delhi"]

// ToString() - Returns a string representing the specified array and its elements
console.log(fruits.toString()); // Output: "Apple,Banana,Cherry"

// join() - Joins all elements of an array into a string
console.log(fruits.join(", ")); // Output: "Apple, Banana, Cherry"

// indexOf() - Returns the first index at which a given element can be found in the array, or -1 if it is not present
console.log(fruits.indexOf("Banana")); // Output: 1

// lastIndexOf() - Returns the last index at which a given element can be found in the array, or -1 if it is not present
console.log(fruits.lastIndexOf("Banana")); // Output: 1

// includes() - Checks if an array contains the specified element
console.log(fruits.includes("Banana")); // Output: true