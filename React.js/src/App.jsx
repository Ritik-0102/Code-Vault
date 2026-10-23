import React from 'react'
import Functions from './Functions'
import UseState from './UseState'
import Form_Handling from './Form_Handling'
import Two_Way_Binding from './Two_Way_Binding'

const App = () => {
  return (
    <div>

      Hello World!

      <Functions />
      <hr />

      <UseState />
      <hr />

      <h1> Form Handling & Two Way Binding</h1>
      <Form_Handling />
      <Two_Way_Binding />
      <hr />

      <Notes_App />
    </div>

  )
}

export default App
