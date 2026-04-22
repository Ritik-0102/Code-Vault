// Template Literals in JS are a new feature that was introduced in ES6. They are a way to create strings that can contain expressions and variables. Template literals are enclosed in backticks (`) instead of single or double quotes.

let name = "Ritik";
let age = 21;

// Template literals can contain expressions and variables
const message = `Hello, my name is ${name} and I am ${age} years old.`;

console.log(message);

// Template literals can also be multi-line
const multiline = `
  Hello,
  my name is ${name}
  and I am ${age} years old.
`;

console.log(multiline);