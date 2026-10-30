import React from 'react'
import { useState, useEffect } from 'react'

const Use_Effect = () => {

    const [A, setA] = useState(0);
    const [B, setB] = useState(0);

    const IncreaseA = () => {
        setA(A + 1);
    }
    const DecreaseB = () => {
        setB(B - 1);
    }

    useEffect(() => {
        console.log('Use Effect Called when A state is changed');
    }, [A]);

    useEffect(() => {
        console.log('Use Effect Called when B state is changed');
    }, [B]);

  return (
    <div style = {{backgroundColor: 'GrayText', padding: '20px', borderRadius: '10px', textAlign: 'center'}}>
        
      <h1>Hooks - Use Effect</h1>

      <button onClick={IncreaseA} style={{ backgroundColor: 'blue', color: 'white' }}> A = {A}</button>
      <button onClick={DecreaseB} style={{ backgroundColor: 'blue', color: 'white' }}> B = {B}</button>
    
    </div>
  )
}

export default Use_Effect
