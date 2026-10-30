import React from 'react'

const Local_Storage = () => {

    // it is used to clear local storage
    // localStorage.clear();

    // it is used to store any data value into local storage
    // localStorage.setItem('key', 'value');
    // localStorage.setItem('user', 'Ritik');

    // used to get item from local storage
    // const value = localStorage.getItem('key');
    // const user = localStorage.getItem('user');
    // console.log(user);

    // used to remove item from local storage
    // localStorage.removeItem('key');

    // How to store objects (Arrays) in local storage :-

    // const data = { name: 'John', age: 30 };
    // to store an object , we need to convert it into a string using JSON.stringify() method
    // localStorage.setItem('data', JSON.stringify(data));

    // to retrieve the object from local storage, we need to parse it back into an object using JSON.parse() method
    // const retrievedData = JSON.parse(localStorage.getItem('data'));


  return (
    <div>
      <h1>Local Storage</h1>
    </div>
  )
}

export default Local_Storage
