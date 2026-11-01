import {Routes,Route} from 'react-router-dom'
import Navbar from './Components/Navbar'
import Home from './Pages/Home'
import About from './Pages/About'
import Contact from './Pages/Contact'

const React_Router_DOM = () => {
  return (
    <div style={{backgroundColor:'chocolate' , color:'white', height:'500px'}}>
        <h1>React Router DOM</h1>

        <Navbar />

        <Routes>
            <Route path='/' element={<Home />} />
            <Route path='/about' element={<About />} />
            <Route path='/contact' element={<Contact />} />
        </Routes>
    </div>
  )
}

export default React_Router_DOM
