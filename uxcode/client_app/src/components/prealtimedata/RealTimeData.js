import React, {Component} from "react";
import {withStyles} from "@material-ui/core/styles";
import Fab from "@material-ui/core/Fab";
import Button from "@material-ui/core/Button";
import Snackbar from "@material-ui/core/Snackbar";
import List from "@material-ui/core/List";
import ListItem from "@material-ui/core/ListItem";
import ListItemText from "@material-ui/core/ListItemText";
import {ReactComponent as HandIconWhite} from "../../images/hand_white.svg";
import Dialog from "@material-ui/core/Dialog";
import DialogContent from "@material-ui/core/DialogContent";
import DialogContentText from "@material-ui/core/DialogContentText";
import DialogTitle from "@material-ui/core/DialogTitle";
import CircularProgress from "@material-ui/core/CircularProgress";

class RealTimeData extends Component {
  constructor(props) {
    super(props);
    this.state = {
      openLoadingDialog: true,
      buttonText: "Start Real Time Play",
      openSnackBar: false,
      snackBarText: "Impulse started succesfully. Please start the game.",
      logs: [],
      openLoadingDialog: false
    };

    this.isRealTimeRunning = false;
  }

  toggleGamePlay = () => {
    const {ipcRenderer} = window.require("electron");
    if (this.isRealTimeRunning == false) {
      ipcRenderer.send("socket_data_send", "start_real_time");
      this.isRealTimeRunning = true;
    } else if (this.isRealTimeRunning == true) {
      this.setState({openLoadingDialog: true});
      ipcRenderer.send("socket_data_send", "stop_real_time");
      this.isRealTimeRunning = false;
    }
  };

  componentDidMount = () => {
    var tmp = [];
    for (var i = 0; i < 20; i++) {
      tmp.push("--");
    }
    this.setState({logs: tmp});

    const {ipcRenderer} = window.require("electron");
    ipcRenderer.on(
      "socket_data_received",
      function(event, data) {
        try {
          var jsonObject = JSON.parse(String(data));
          if (jsonObject.type == "start_real_time_success") {
            this.setState({buttonText: "Stop Real Time Play", snackBarText: "Impulse started succesfully. Please start the game.", openSnackBar: true});
            setTimeout(
              function() {
                this.setState({openSnackBar: false});
              }.bind(this),
              4000
            );
          } else if (jsonObject.type == "stop_real_time_success") {
            console.log(String(data));
            this.setState({buttonText: "Start Real Time Play", snackBarText: "Stopped succesfully!!.", openSnackBar: true, openLoadingDialog: false});
            setTimeout(
              function() {
                this.setState({openSnackBar: false});
              }.bind(this),
              4000
            );
          } else if (jsonObject.type == "real_time_logs") {
            var jsonObject = JSON.parse(String(data));
            var arrayTmp = this.state.logs;
            arrayTmp = arrayTmp.concat(jsonObject.logs);
            if (arrayTmp.length > 20) {
              arrayTmp.splice(0, arrayTmp.length - 20);
            }
            this.setState({logs: arrayTmp});
          }
        } catch (e) {
          console.log("Error in paring data ");
          console.log(data);
          console.log(e);
        }
      }.bind(this)
    );
  };

  render() {
    const {classes} = this.props;
    return (
      <div style={{height: "100%", width: "100%"}}>
        <div style={{display: "flex", flexDirection: "column", justifyContent: "start", height: "100%", padding: "2%"}}>
          <div style={{display: "flex", justifyContent: "center"}}>
            <h4>
              <u>Real Time Data</u>
            </h4>
          </div>

          <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "column"}}>
            <List dense className={classes.root}>
              {this.state.logs.map((value) => {
                return (
                  <ListItem>
                    <ListItemText primary={value} />
                  </ListItem>
                );
              })}
            </List>
          </div>

          <div style={{display: "flex", justifyContent: "center", paddingTop: 10}}>
            <Fab variant="extended" color="primary" aria-label="Add" onClick={this.toggleGamePlay} className={classes.margin}>
              <HandIconWhite className={classes.extendedIcon} />
              {this.state.buttonText}
            </Fab>
          </div>
        </div>

        <Snackbar anchorOrigin={{vertical: "bottom", horizontal: "left"}} open={this.state.openSnackBar} ContentProps={{"aria-describedby": "message-id"}} message={<span id="message-id">{this.state.snackBarText}</span>} />

        <Dialog
          open={this.state.openLoadingDialog}
          // onClose={this.closeLoadingDialog}
          aria-labelledby="alert-dialog-title"
          aria-describedby="alert-dialog-description"
          disableBackdropClick={true}
          disableEscapeKeyDown={true}
          style={{display: "flex", justifyContent: "center", flexDirection: "column"}}>
          <div style={{display: "flex", justifyContent: "center"}}>
            <DialogTitle id="alert-dialog-title">{"Impulse Message."}</DialogTitle>
          </div>
          <DialogContent style={{display: "flex", justifyContent: "center", flexDirection: "column"}}>
            <div>
              <div style={{display: "flex", justifyContent: "center"}}>
                <CircularProgress className={classes.progress} />
              </div>
              <div style={{display: "flex", justifyContent: "center", paddingTop: 15}}>
                <DialogContentText id="alert-dialog-description"> {"Saving Results..."}</DialogContentText>
              </div>
            </div>
          </DialogContent>
        </Dialog>
      </div>
    );
  }
}

const styles = (theme) => ({
  margin: {
    margin: theme.spacing.unit
  },
  extendedIcon: {
    marginRight: theme.spacing.unit
  }
});

export default withStyles(styles, {withTheme: true})(RealTimeData);
