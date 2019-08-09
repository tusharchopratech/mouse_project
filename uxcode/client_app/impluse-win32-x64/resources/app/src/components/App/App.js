import React, {Component, Fragment} from 'react';
import './App.css';
import HomeScreen from '../phomescreen/HomeScreen';


class App extends Component {

  componentDidMount(){
    document.title = "Brink Bionics"
  }

  render() {
    return (
      <Fragment>
        <HomeScreen></HomeScreen>
      </Fragment>
    );
  }
}

export default App;
