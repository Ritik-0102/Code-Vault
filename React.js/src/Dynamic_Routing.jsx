import { Route, Routes } from "react-router-dom"
import Navbar1 from "./Components/Navbar1"
import Navbar2 from "./Components/Navbar2"
import Footer from "./Components/Footer"
import Home from "./Pages/Home"
import About from "./Pages/About"
import Collection from "./Pages/Collection"
import Contact from "./Pages/Contact"
import Men from "./Pages/Men"
import Women from "./Pages/Women"
import Kids from "./Pages/Kids"
import PageNotFound from "./Pages/PageNotFound"
import Dynamic_Routed_Page from "./Pages/Dynamic_Routed_Page"

const Dynamic_Routing = () => {
  return (
    <div className='flex flex-col bg-gray-600 h-120 '>
      <h1>Dynamic Routing</h1>

      <div className='flex justify-between px-8 items-center bg-gray-500 text-amber-50'>
        <Navbar1 />
        <Navbar2 />
      </div>
      

      <div className="flex-grow">
        <Routes>

          <Route path="/" element = {<Home />} />
          <Route path="/about" element = {<About />} />◘

          {/* It shows Dynamic Routing */}
          <Route path="/about/:anything" element = {<Dynamic_Routed_Page />} />

          <Route path="/collection" element = {<Collection />}>
            <Route path="mens" element = {<Men />} />
            <Route path="womens" element = {<Women />} />
            <Route path="kids" element = {<Kids />} />
          </Route>

          <Route path="/contact" element = {<Contact />} />

          {/* Used to Route to show a page when a user typed any randow link */}
          <Route path="*" element = {<PageNotFound />} />
        </Routes>
      </div>

      <Footer />
    </div>
  )
}

export default Dynamic_Routing
