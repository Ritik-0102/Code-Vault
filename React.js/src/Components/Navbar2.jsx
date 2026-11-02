import { Link } from "react-router-dom"

const Navbar2 = () => {
  return (
    <div className="flex gap-10">
      <Link to = '/' className="text-amber-50">Home</Link>
      <Link to = '/about' className="text-amber-50">About</Link>
      <Link to = '/collection'  className="text-amber-50">Collection</Link>
      <Link to = '/contact'  className="text-amber-50">Contact</Link>
    </div>
  )
}

export default Navbar2
