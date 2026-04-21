// String are Immutable In JavaScript, which means that once a string is created, it cannot be changed. However, you can create a new string based on the original string.

let name = "Ritik";

// String length
console.log(name.length);

// String indexing
for(let i = 0; i < name.length; i++) {
    console.log(name[i] + " is at index " + i);
}

// String iteration using for-of loop
for(let char of name) {
    console.log(char);
}



// String Methods in JS :-

// toUpperCase() - Converts a string to uppercase letters
console.log(name.toUpperCase()); // Output: RITIK

// toLowerCase() - Converts a string to lowercase letters
console.log(name.toLowerCase()); // Output: ritik

// charAt() - Returns the character at the specified index
console.log(name.charAt(0)); // Output: R

// indexOf() - Returns the index of the first occurrence of a specified value in a string
console.log(name.indexOf("i")); // Output: 1

// lastIndexOf() - Returns the index of the last occurrence of a specified value in a string
console.log(name.lastIndexOf("i")); // Output: 4

// includes() - Checks if a string contains a specified value
console.log(name.includes("i")); // Output: true

// startsWith() - Checks if a string starts with a specified value
console.log(name.startsWith("R")); // Output: true

// endsWith() - Checks if a string ends with a specified value
console.log(name.endsWith("k")); // Output: true    

// Trim() - Removes whitespace from both ends of a string
let nameWithSpaces = "   Ritik Rana  ";
console.log(nameWithSpaces.trim()); // Output: "Ritik Rana"

// String concatenation
let firstName = "Ritik";
let lastName = "Rana";
let fullName = firstName.concat(" ", lastName);
console.log(fullName); // Output: Ritik Rana

// String slicing
console.log(name.slice(0, 3)); // Output: Rit

// String replacing
console.log(name.replace("i", "u")); // Output: Rutik

// String repeating
console.log("Ritik".repeat(3)); // Output: RitikRitikRitik

// String splitting
let nameArray = name.split("");
console.log(nameArray); // Output: ["R", "i", "t", "i", "k"]

// String joining
nameArray = ["R", "i", "t", "i", "k"];
console.log(nameArray.join("")); // Output: Ritik