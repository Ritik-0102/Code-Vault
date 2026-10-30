import React , {useState} from 'react'
import './Notes_App.css'

const Notes_App = () => {

  const [notes, setNotes] = useState([])

  const [title, setTitle] = useState('')
  const [description, setDescription] = useState('')

  const AddNote = (e) => {
    e.preventDefault()

    const temp = [...notes];

    temp.push({title,description});

    setNotes(temp);

    setTitle('')
    setDescription('')

  }

  return (
    <div className='notes-app'>
      <h1> Notes App</h1>

      <form onSubmit = {(e) =>
        AddNote(e)
        }>

        <input type="text"
          placeholder='Title' 
          value={title}
          
          onChange = { (e) => {
            setTitle(e.target.value);
          }}

          />
        
        <textarea placeholder='Description'
          value={description}

          onChange={(e) => {
            setDescription(e.target.value);
          }}
          ></textarea>
        
        <button> Add Note</button>
      </form>
      <div>
        <h1>Saved Notes</h1>
        
        <div className='notes'>
          
        {notes.map(function (e,idx) {
          return <div key={idx} className='note'>
            <h2>{e.title}</h2>
            <p>{e.description}</p>
          </div>
        })}

        </div>
      </div>
    </div>
  )
}

export default Notes_App
