// try-catch-finally block :-  

try {

  // ... normal code

} catch ( err ) { // err is error object

  // ... handling error
} finally {

  // ... code to be executed regardless of whether an error occurred or not
}

// If you need code to run only when no error occurred, place it after the try-catch-finally block.


// Error Object :-
// It is a special object that has details about the error.

console.log(err.name); // Error name
console.log(err.message); // Error message
console.log(err.stack); // Error stack  
