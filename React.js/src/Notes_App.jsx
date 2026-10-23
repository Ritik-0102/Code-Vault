import React from 'react'
import './Notes_App.css'

const Notes_App = () => {
  return (
    <div className='notes-app'>
      <h1> Notes App</h1>

      <form>
        <input type="text" placeholder='Title' />
        
        <textarea placeholder='Description'></textarea>
        
        <button> Add Note</button>
      </form>
    </div>
  )
}

export default Notes_App
