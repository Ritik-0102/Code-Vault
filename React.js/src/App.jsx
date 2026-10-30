import React from 'react'
import Functions from './Functions'
import UseState from './UseState'
import Form_Handling from './Form_Handling'
import Two_Way_Binding from './Two_Way_Binding'
import Notes_App from './Notes_App'
import Local_Storage from './Local_Storage'
import API from './API_Calls'
import Use_Effect from './Use_Effect'
import Gallery_App from './Gallery_App'

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
      <hr />

      <Local_Storage />
      <hr />

      <API />
      <hr />

      <Use_Effect />
      <hr />

      <Gallery_App />
      <hr />
    </div>

  )
}

export default App
