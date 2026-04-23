// forEach() - Iterates over an array, executing a provided function once for each array element
// It does not return a new array, but it can be used to perform side effects on each element of the array. The forEach() method takes a callback function as an argument, which is executed for each element in the array. The callback function can take three arguments: the current element being processed, the index of the current element, and the array that forEach() was called upon.

let fruits = ["Apple", "Banana", "Cherry"];

fruits.forEach(function(fruit) {
    console.log(fruit);
});


// map() - Creates a new array with the results of calling a provided function on every element in this array
let newArray = fruits.map(function(fruit) {
    return fruit.toUpperCase();
});
console.log(newArray); // Output: ["APPLE", "BANANA", "CHERRY"]


// filter() - Creates a new array with every element in this array that pass a test
let filteredArray = fruits.filter(function(fruit) {
    return fruit !== "Apple";
});
console.log(filteredArray); // Output: ["Banana", "Cherry"]


// reduce() - Apply a function against an accumulator and each value of the array (from left-to-right) as to reduce it to a single value
let array = [1, 2, 3, 4];
let total = array.reduce(function(accumulator, currentValue) {
    return accumulator + currentValue;
});
console.log(total); // Output: 10