import React from 'react'

const UseState = () => {

  let a = 0;

  function btnClick() {
    console.log('Button clicked');
    a++;
    console.log(a);
  }

  return (
    <div>
      <h1> Hooks - UseState </h1>

      <button onClick={btnClick}>Click Me</button>
      
    </div>
  )
}

export default UseState
