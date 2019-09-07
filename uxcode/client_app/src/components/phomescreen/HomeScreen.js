import React, { Component } from 'react'
import { withStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import CssBaseline from '@material-ui/core/CssBaseline';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import Grid from '@material-ui/core/Grid';
import MyDrawer from './MyDrawer';
import Caliberation from '../pcaliberation/Caliberation';
import UserTraining from '../pusertraning/UserTraining';
import RealTimeData from '../prealtimedata/RealTimeData';
import Welcome from '../pwelcome/Welcome';
import Report from '../preport/Report';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';
import CircularProgress from '@material-ui/core/CircularProgress';
import LinearProgress from '@material-ui/core/LinearProgress';


export class HomeScreen extends Component {

  constructor(props) {
    super(props)
    this.left = 0;
    this.right = 0;
    this.top = 0;
    this.bottom = 0;
    this.width = 10;
    this.height = 10;
    this.report = null;
    this.containerRef = React.createRef()
    this.state = {
      current_screen: '',
      openLoadingDialog: true,
      openLoadingDialogPercentage: 27,
      openLoadingDialogText: ""
    }
  }

  setMainSection = (val) => {
    this.setState({ current_screen: val });
  };

  setMainSectionWithData = (val, data) => {
    this.report = data;
    this.setState({ current_screen: val });
  };

  getMainSectionComponent = (val) => {
    if (val === "caliberation") {
      return <Caliberation callbackSetMainSection={this.setMainSection} />
    } else if (val === "user_training") {
      return <UserTraining myTop={this.top} myBottom={this.bottom} myLeft={this.left} myRight={this.right} callbackSetMainSection={this.setMainSectionWithData} />
    } else if (val === "real_time_data") {
      return <RealTimeData />
    } else if (val === "report") {
      return <Report report={this.report} />
    } else if (val === "welcome") {
      return <Welcome callbackSetMainSection={this.setMainSection} />
    }
  };

  componentDidMount = () => {
    this.left = this.containerRef.current.offsetLeft;
    this.right = this.left + this.containerRef.current.offsetWidth
    this.top = 0
    this.bottom = this.top + this.containerRef.current.offsetHeight;
    this.setState({ current_screen: 'welcome' });
    console.log("Homescreen mounted");

    const { ipcRenderer } = window.require("electron");
    ipcRenderer.send("internal_ipc", "start_backend_and_socket");
    ipcRenderer.on('internal_ipc', function (event, data) {
      console.log(data);
      try {
        var jsonObject = JSON.parse(String(data));
        if (jsonObject.type == "status" && jsonObject.value == "backend_disconnected") {
          this.setState({ openLoadingDialogPercentage: 63, openLoadingDialog: true });
        } else if (jsonObject.type == "status" && jsonObject.value == "socket_connected") {
          this.setState({ openLoadingDialogPercentage: 100, openLoadingDialog: false });
        } else if (jsonObject.type == "status" && jsonObject.value == "socket_disconnected") {
          this.setState({ openLoadingDialogText: "Please press Ctrl + R", openLoadingDialog: true });
        }
      } catch (e) {
        console.log("Error in paring data ");
        console.log(data);
        console.log(e);
      }
    }.bind(this));

    ipcRenderer.on('internal_ipc_error', function (event, data) {
      console.log("Internal IPC Error");
      console.log(data);
    }.bind(this));

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

        <Dialog
          open={this.state.openLoadingDialog}
          // onClose={this.closeLoadingDialog}
          aria-labelledby="alert-dialog-title"
          aria-describedby="alert-dialog-description"
          disableBackdropClick={true}
          disableEscapeKeyDown={true}
        >
          <DialogTitle id="alert-dialog-title">{"Setting Up Please Wait.."}</DialogTitle>
          <DialogContent>
            <DialogContentText id="alert-dialog-description"> {this.state.openLoadingDialogText}</DialogContentText>
            <LinearProgress variant="determinate" value={this.state.openLoadingDialogPercentage} />
          </DialogContent>
        </Dialog>
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