import React, { Component } from 'react'
import { withStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import CssBaseline from '@material-ui/core/CssBaseline';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import Grid from '@material-ui/core/Grid';
import MyDrawer from './MyDrawer';
import Caliberation from '../pcaliberation/Caliberation2';
import UserTraining from '../pusertraning/UserTraining';
import RealTimeData from '../prealtimedata/RealTimeData';
import Welcome from '../pwelcome/Welcome';
import Report from '../preport/Report';


export class HomeScreen extends Component {

  constructor(props) {
    super(props)
    this.left = 0;
    this.right = 0;
    this.top = 0;
    this.bottom = 0;
    this.width = 10;
    this.height = 10;
    this.containerRef = React.createRef()
    this.state = {
      current_screen: ''
    }
  }

  setMainSection = (val) => {
    this.setState({ current_screen: val });
  };

  getMainSectionComponent = (val) => {
    if (val === "caliberation") {
      return <Caliberation callbackSetMainSection={this.setMainSection} myTop={this.top} myBottom={this.bottom} myLeft={this.left} myRight={this.right} />
    } else if (val === "user_training") {
      return <UserTraining />
    } else if (val === "real_time_data") {
      return <RealTimeData />
    } else if (val === "report") {
      return <Report />
    } else if (val === "welcome") {
      return <Welcome  callbackSetMainSection={this.setMainSection} />
    }
  };

  componentDidMount = () => {
    this.left=this.containerRef.current.offsetLeft;
    this.right = this.left+this.containerRef.current.offsetWidth
    this.top=0
    this.bottom= this.top+ this.containerRef.current.offsetHeight;
    this.setState({ current_screen: 'welcome' });
  };

  render() {
    const { classes } = this.props;
    return (
      <div className={classes.root}>
        {/* <IOHook/> */}
        <CssBaseline />
        <AppBar position="fixed" className={classes.appBar}>
          <Toolbar>
            <Typography variant="h6" color="inherit" noWrap>
              Gaming Tech
          </Typography>
          </Toolbar>
        </AppBar>
        <MyDrawer callbackSetMainSection={this.setMainSection} />

          {/* <div ref={this.containerRef} > */}
          <main ref={this.containerRef} className={classes.content}>
       
            <div className={classes.toolbar} />
            <Grid container direction='column' alignItems='center' justify='center' className={classes.main_content}>
                {this.getMainSectionComponent(this.state.current_screen)}
            </Grid>
            
          </main>
          {/* </div>  */}
      </div>
    )
  }
}


const styles = theme => ({
  root: {
    display: 'flex',
  },
  appBar: {
    zIndex: theme.zIndex.drawer + 1,
  },
  content: {
    height: '100vh',
    flexGrow: 1,
    paddingBottom: 38,
  },
  // toolbar: theme.mixins.toolbar,
  toolbar: {
    height: '7%',
  },
  main_content: {
    height: '100%',
  }
});

export default withStyles(styles, { withTheme: true })(HomeScreen);