import React, { useState } from 'react'

const Two_Way_Binding = () => {

  const [title, setTitle] = useState('');

  const submitHandler = (e) => {
    e.preventDefault();
    console.log("Form Submitted By : ", title);

    // Reset the Form after Buttom is pressed
    setTitle('');
  } 
  
  return (
    <div>
      <form onSubmit = {(e) => {
        submitHandler(e);
      }} >
        <input type='text' placeholder='Enter Your Name' 
              value={title} 
              onChange={(e) => setTitle(e.target.value)} />
        <button>Submit</button>
      </form>
    </div>
  )
}

export default Two_Way_Binding
