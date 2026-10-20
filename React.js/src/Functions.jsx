import React from 'react'

const App = () => {

  function btnClick() {
    console.log('Button clicked');
  }

  function mouseEnter(){
    console.log('Mouse entered');
  }

  function inputChanging(val){
    console.log(val);
  }

  function onScroll(elem){
    console.log(elem.target.scrollTop);
  }

  return (
    <div>
      <h1> Functions </h1>

      <button onClick={btnClick} onMouseEnter={mouseEnter}>Click Me</button>

      <button onClick={() => {
        console.log('Button clicked with arrow function')
      }}>Click Me</button>

      <input type="text" onChange={function(elem){
        inputChanging(elem.target.value);
      }}  placeholder='Enter some Text'/>

      <div onScroll={onScroll}>
        Scroll Me
      </div>
      

    </div>
  )
}

export default App
