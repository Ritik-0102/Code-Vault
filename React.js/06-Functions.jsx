import React from 'react'

const App = () => {

  function btnClick() {
    console.log('Button clicked');
  }

  function mouseEnter(){
    console.log('Mouse entered');
  }

  return (
    <div>
      console.log("Hello");

      <button onClick={btnClick} onMouseEnter={mouseEnter}>Click Me</button>
    </div>
  )
}

export default App
