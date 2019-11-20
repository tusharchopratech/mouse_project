import React, {Component} from "react";
import {withStyles} from "@material-ui/core/styles";
import Fab from "@material-ui/core/Fab";
import ReactDOM from "react-dom";
import Button from "@material-ui/core/Button";
import Dialog from "@material-ui/core/Dialog";
import DialogActions from "@material-ui/core/DialogActions";
import DialogContent from "@material-ui/core/DialogContent";
import DialogContentText from "@material-ui/core/DialogContentText";
import DialogTitle from "@material-ui/core/DialogTitle";
import {ReactComponent as MouseIcon} from "../../images/mouse_white.svg";
import CircularProgress from "@material-ui/core/CircularProgress";
import TextField from "@material-ui/core/TextField";
import Snackbar from "@material-ui/core/Snackbar";
import SignalComponent from "../psignalscomp/SignalsComp";
import Select from "@material-ui/core/Select";
import InputLabel from "@material-ui/core/InputLabel";
import MenuItem from "@material-ui/core/MenuItem";
import FormControl from "@material-ui/core/FormControl";

class UserTraining extends Component {
  constructor(props) {
    super(props);
    this.signalComponentRef = React.createRef();
    this.left = this.props.myLeft + 50; // adding 50 for bounday offset
    this.right = this.props.myRight - 120; // bounday offset including width of the button
    this.top = this.props.myTop + 64 + 50; // adding 64 for toolbar, 50 for boundary off set
    this.bottom = this.props.myBottom - 80; // boundary offset including height of the button
    this.clickSequence = [];

    this.tfNoClicks = 5;
    this.tfPName = "tushar";
    this.tfnoChannels = 4;
    this.tfTrainNo = 1;
    this.tfClickType = "both";

    this.currentClickType = "both";
    this.leftClickId = 0;
    this.rightClickId = 2;
    this.thumb1ClickId = 3;
    this.thumb2ClickId = 4;

    this.i = 0;
    this.click_info = {
      up: null,
      down: null
    };
    this.clicksInfoArray = [];
    this.state = {
      start_showing_random_clicks: false,
      openLoadingDialogForUserTraining: false,
      openConfigDialog: true,
      settingsErrorMessage: "",
      openSnackBar: false
    };
  }

  renderTest = (val) => {
    if (val === true) {
      // console.log("I run ", this.i);
      if (this.i < this.clickSequence.length) {
        this.currentClickType = this.clickSequence[this.i];
        this.i++;
        this.x = this.top + Math.random() * (this.bottom - this.top);
        this.y = this.left + Math.random() * (this.right - this.left);
        return (
          <Fab size="small" variant="extended" color="primary" aria-label="Add" ref="test_click_button" style={{position: "absolute", top: this.x, left: this.y}} onMouseDown={this.onMouseDown.bind(this)}>
            {" "}
            Click {this.currentClickType}!
          </Fab>
        );
      } else {
        console.log("Done Test");
        this.setState({
          start_showing_random_clicks: false,
          showCaliberationButton: false,
          openLoadingDialogForUserTraining: true
        });
        const {ipcRenderer} = window.require("electron");
        ipcRenderer.send("socket_data_send", "stop_training");
      }
    } else {
      return;
    }
  };

  onClickStartTraining = (event) => {
    if (window.require("electron").remote.getGlobal("shared_object").current_envirnoment == "dev") {
      this.setState({
        start_showing_random_clicks: false,
        showCaliberationButton: false,
        openLoadingDialogForUserTraining: true
      });
      const {ipcRenderer} = window.require("electron");
      ipcRenderer.send("socket_data_send", "stop_training");
    } else {
      const {ipcRenderer} = window.require("electron");
      ipcRenderer.send("socket_data_send", "start_training");
      ReactDOM.findDOMNode(this.refs.start_caliberation_button).style.display = "none";
      setTimeout(
        function() {
          this.setState({
            start_showing_random_clicks: true
          });
        }.bind(this),
        2000
      );
    }
  };

  handleTfChange = (name, event) => {
    if (name == "tf_no_of_clicks") {
      this.tfNoClicks = event.target.value;
    }
    if (name == "tf_p_name") {
      this.tfPName = event.target.value;
    }
    if (name == "tf_no_channels") {
      this.tfnoChannels = event.target.value;
    }
    if (name == "tf_trail_no") {
      this.tfTrainNo = event.target.value;
    }
    if (name == "select_click_type") {
      this.tfClickType = event.target.value;
    }
  };

  sendSettings = (event) => {
    var noClicks = this.tfNoClicks;
    var pName = this.tfPName;
    var noChannels = this.tfnoChannels;
    var trainNo = this.tfTrainNo;
    var clickType = this.tfClickType;
    if (isNaN(noClicks) == false && parseInt(noClicks) >= 5 && parseInt(noClicks) <= 50) {
      if (pName != "") {
        if (isNaN(noChannels) == false && parseInt(noChannels) >= 1 && parseInt(noChannels) <= 4) {
          if (isNaN(trainNo) == false && parseInt(trainNo) >= 1) {
            const {ipcRenderer} = window.require("electron");
            var json = JSON.stringify({type: "communication", value: "settings", participant_name: pName, no_of_channels: parseInt(noChannels), trail_no: parseInt(trainNo), click_type: clickType});
            console.log(json);
            ipcRenderer.send("socket_data_send", json);

            for (var i = 0; i < this.tfNoClicks; i++) {
              this.clickSequence.push("left");
            }
            for (var i = 0; i < this.tfNoClicks; i++) {
              this.clickSequence.push("right");
            }
            for (var i = 0; i < this.tfNoClicks; i++) {
              this.clickSequence.push("thumb");
            }
            this.clickSequence = this.shuffleArray(this.clickSequence);
          } else {
            this.setState({settingsErrorMessage: "Train Number should be a positive integer, >=1", openSnackBar: true});
            setTimeout(
              function() {
                this.setState({openSnackBar: false});
              }.bind(this),
              4000
            );
          }
        } else {
          this.setState({settingsErrorMessage: "Number of channels should be between 1 to 4.", openSnackBar: true});
          setTimeout(
            function() {
              this.setState({openSnackBar: false});
            }.bind(this),
            4000
          );
        }
      } else {
        this.setState({settingsErrorMessage: "Participant name cannot be blank", openSnackBar: true});
        setTimeout(
          function() {
            this.setState({openSnackBar: false});
          }.bind(this),
          4000
        );
      }
    } else {
      this.setState({settingsErrorMessage: "Number of click should be a positive number and between 5 and 50.", openSnackBar: true});
      setTimeout(
        function() {
          this.setState({openSnackBar: false});
        }.bind(this),
        4000
      );
    }
  };

  onMouseDown = (event) => {
    // console.log(event.button);
    if (this.state.start_showing_random_clicks) {
      if (this.currentClickType == "left") {
        if (event.button != this.leftClickId) {
          return;
        }
      } else if (this.currentClickType == "right") {
        if (event.button != this.rightClickId) {
          return;
        }
      } else if (this.currentClickType == "thumb") {
        if (!(event.button == this.thumb1ClickId || event.button == this.thumb2ClickId)) {
          return;
        }
      }
    }
    this.setState({
      start_showing_random_clicks: true
    });

    if (ReactDOM.findDOMNode(this.refs.test_click_button) != null) {
      ReactDOM.findDOMNode(this.refs.test_click_button).style.display = "none";
    }

    setTimeout(
      function() {
        if (ReactDOM.findDOMNode(this.refs.test_click_button) != null) {
          ReactDOM.findDOMNode(this.refs.test_click_button).style.display = "";
        }
      }.bind(this),
      2000
    );
  };

  componentDidMount = () => {
    console.log("User Training Component Mounted");
    this.right = this.right - document.getElementById("signal-section-div").clientWidth;
    const {ipcRenderer} = window.require("electron");
    ipcRenderer.on(
      "socket_data_received",
      function(event, data) {
        try {
          var jsonObject = JSON.parse(String(data));
          if (jsonObject.type == "algo_outputs") {
            console.log(jsonObject);
            this.setState({
              start_showing_random_clicks: false,
              showCaliberationButton: false,
              openLoadingDialogForUserTraining: false
            });
            this.props.callbackSetMainSection("report", jsonObject);
          } else if (jsonObject.type == "communication_success" && jsonObject.value == "settings_set") {
            console.log("Configuration Set!!");
            this.setState({
              openConfigDialog: false
            });
          } else if (jsonObject.type == "real_time_training_data") {
            // console.log(jsonObject);
            this.signalComponentRef.addPoints(jsonObject);
          }
        } catch (e) {
          console.log("Error in paring data ", String(data));
          console.log(e);
        }
      }.bind(this)
    );
  };

  componentWillUnmount = () => {
    console.log("User Training  Component Unmounted!!");
    const {ipcRenderer} = window.require("electron");
    ipcRenderer.removeAllListeners("socket_data_received");
  };

  shuffleArray = (arra1) => {
    var ctr = arra1.length,
      temp,
      index;
    while (ctr > 0) {
      index = Math.floor(Math.random() * ctr);
      ctr--;
      temp = arra1[ctr];
      arra1[ctr] = arra1[index];
      arra1[index] = temp;
    }
    return arra1;
  };

  render() {
    const {classes} = this.props;
    return (
      <div style={{height: "100%", width: "100%"}}>
        <div style={{display: "flex", height: "100%", alignItems: "center", flexDirection: "row"}}>
          <div style={{flex: 2, display: "flex", height: "100%", alignItems: "center"}}>
            <div id="test-section-div" style={{textAlign: "center", width: "100%"}}>
              <Fab variant="extended" color="primary" aria-label="Add" ref="start_caliberation_button" onMouseDown={this.onClickStartTraining.bind(this)} className={classes.margin}>
                <MouseIcon className={classes.extendedIcon} />
                Start Training
              </Fab>
              {this.renderTest(this.state.start_showing_random_clicks)}
            </div>
          </div>
          <div id="signal-section-div" style={{flex: 1, display: "flex", height: "100%", alignItems: "center", borderLeft: "1px solid #dcdcdc", padding: "10px"}}>
            <div style={{display: "flex", flexDirection: "column", width: "100%", alignItems: "center"}}>
              <h5 style={{paddingBottom: "10px"}}>Real Time Signals</h5>
              <SignalComponent onRef={(ref) => (this.signalComponentRef = ref)} parentComponentName={"user_training"} />
            </div>
          </div>
        </div>

        <Dialog open={this.state.openLoadingDialogForUserTraining} aria-labelledby="alert-dialog-title" aria-describedby="alert-dialog-description" disableBackdropClick={true} disableEscapeKeyDown={true} style={{display: "flex", justifyContent: "center", flexDirection: "column"}}>
          <div style={{display: "flex", justifyContent: "center"}}>
            <DialogTitle id="alert-dialog-title">{"Impulse Message."}</DialogTitle>
          </div>
          <DialogContent style={{display: "flex", justifyContent: "center", flexDirection: "column"}}>
            <div>
              <div style={{display: "flex", justifyContent: "center"}}>
                <CircularProgress className={classes.progress} />
              </div>
              <div style={{display: "flex", justifyContent: "center", paddingTop: 15}}>
                <DialogContentText id="alert-dialog-description"> {"Extracting Information..."}</DialogContentText>
              </div>
            </div>
          </DialogContent>
        </Dialog>

        <Dialog open={this.state.openConfigDialog} aria-labelledby="alert-dialog-title" aria-describedby="alert-dialog-description" disableBackdropClick={true} disableEscapeKeyDown={true} style={{display: "flex", justifyContent: "center", flexDirection: "column"}}>
          <div style={{display: "flex", justifyContent: "center"}}>
            <DialogTitle id="alert-dialog-title">{"Training Configuration"}</DialogTitle>
          </div>
          <DialogContent style={{display: "flex", justifyContent: "center", flexDirection: "column"}}>
            <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "column"}}>
              <div style={{flex: 1}}>
                <TextField type="number" value={this.tfNoClicks} label="Number of Clicks" className={classes.textField} margin="normal" onChange={this.handleTfChange.bind(this, "tf_no_of_clicks")} variant="outlined" />
              </div>
              <div style={{flex: 1}}>
                <TextField label="Participant Name" value={this.tfPName} className={classes.textField} margin="normal" onChange={this.handleTfChange.bind(this, "tf_p_name")} variant="outlined" />
              </div>
              <div style={{flex: 1}}>
                <TextField type="number" value={this.tfnoChannels} label="Number Of Channels" className={classes.textField} margin="normal" onChange={this.handleTfChange.bind(this, "tf_no_channels")} variant="outlined" />
              </div>
              <div style={{flex: 1}}>
                <TextField type="number" value={this.tfTrainNo} label="Trial Number" className={classes.textField} margin="normal" onChange={this.handleTfChange.bind(this, "tf_trail_no")} variant="outlined" />
              </div>
              <div style={{flex: 1, width: "100%"}}>
                <FormControl className={classes.formControl} style={{width: "100%"}}>
                  <InputLabel>Click Type</InputLabel>
                  <Select onChange={this.handleTfChange.bind(this, "select_click_type")} value={"both"}>
                    <MenuItem value={"left"}>Left</MenuItem>
                    <MenuItem value={"right"}>Right</MenuItem>
                    <MenuItem value={"both"}>Both</MenuItem>
                    {/* <MenuItem value={"both"}>Both</MenuItem> */}
                  </Select>
                </FormControl>
              </div>

              <div style={{display: "flex", justifyContent: "center", paddingTop: 15}}>
                <Button variant="outlined" color="primary" className={classes.button} onClick={this.sendSettings}>
                  Start Training
                </Button>
              </div>
            </div>
          </DialogContent>
        </Dialog>

        <Snackbar
          // key={messageInfo ? messageInfo.key : undefined}
          anchorOrigin={{
            vertical: "bottom",
            horizontal: "left"
          }}
          open={this.state.openSnackBar}
          ContentProps={{
            "aria-describedby": "message-id"
          }}
          message={<span id="message-id">{this.state.settingsErrorMessage}</span>}
        />
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

export default withStyles(styles, {withTheme: true})(UserTraining);
