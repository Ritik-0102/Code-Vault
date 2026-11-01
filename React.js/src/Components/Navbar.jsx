import './Navbar.css'
import { Link } from 'react-router-dom'

const Navbar = () => {
  return (
    <div className='Navbar'>
      <h3>Navbar</h3>
      <div>
        <Link to = '/' className='link'>Home</Link>
        <Link to = '/about' className='link'>About</Link>
        <Link to = '/contact' className='link'>Contact</Link>
      </div>
    </div>
  )
}

export default Navbar
