// async await >> promise chains >> callback hell


// Callbacks
// A callback is a function passed as an argument to another function.

// Callback Hell : Nested callbacks stacked below one another forming a pyramid structure.
// (Pyramid of Doom)


function getData(callback) {
    const response = fetch("https://jsonplaceholder.typicode.com/todos/1");
    response.then(data => {
        callback(data);
    }).catch(err => {
        console.log(err);
    });
}

getData(data => {
    console.log(data);
});


// Promises
// A promise is an object that represents the eventual completion or failure of an asynchronous operation.
// It has three states: pending, fulfilled, or rejected.

// let promise = new Promise( (resolve, reject) => { .... } )
// *resolve & reject are callbacks provided by JS

// *Promise has state (pending, fulfilled) & some
// result (result for resolve & error for reject).

// .then( ) & .catch( ) :-

// promise.then( ( res ) => { .... } )
// promise.catch( ( err ) ) => { .... } )

const getData = () => {
    return new Promise((resolve, reject) => {
        const response = fetch("https://jsonplaceholder.typicode.com/todos/1");
        response.then(data => {
            resolve(data);
        }).catch(err => {
            reject(err);
        });
    });
}

getData().then(data => {
    console.log(data);
}).catch(err => {
    console.log(err);
});


// Async-Await :-

// async function always returns a promise.
// async function myFunc( ) { .... }

// await pauses the execution of its surrounding async function until the promise is settled.

async function getData() {
    const response = await fetch("https://jsonplaceholder.typicode.com/todos/1");
    const data = await response.json();
    return data;
}

getData().then(data => {
    console.log(data);
}).catch(err => {
    console.log(err);
});
