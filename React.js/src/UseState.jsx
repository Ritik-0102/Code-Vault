import React, { useState } from 'react'

const UseState = () => {

  // Initial value of a is 0 with the help of useState hook 
  const [a, setA] = useState(0);

  // Function to change the value of a with the help of setA function
  function IncreaseValue() {
    setA(a + 1);
  }

  function DecreaseValue() {
    setA(a - 1);
  }

  // how to change the values of a Array
  const [arr, setArr] = useState([1, 2, 3]);

  function AddItem() {
    setArr([...arr, 4]);
  }

  // How to change the value of a Object
  const [obj, setObj] = useState({ a: 1, b: 2 });

  function ChangeObj() {
    setObj({ ...obj, a: 2, b: 3 });
  }

  return (
    <div>
      <h1> Hooks - UseState </h1>

      <h2> Value of a is {a} </h2>

      <button onClick={IncreaseValue}> Increase </button>
      <button onClick={DecreaseValue}> Decrease </button>

      <h2> Value of arr is {arr.join(', ')} </h2>
      <button onClick={AddItem}> Add Item </button>

      <h2> Value of obj is a: {obj.a}, b: {obj.b} </h2>
      <button onClick={ChangeObj}> Change Object </button>
    </div>
  )
}

export default UseState
