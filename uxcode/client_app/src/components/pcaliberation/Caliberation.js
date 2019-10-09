import React, {Component} from "react";
import {withStyles} from "@material-ui/core/styles";
import PropTypes, {array} from "prop-types";
import Fab from "@material-ui/core/Fab";
import {Line} from "react-chartjs-2";
import SignalComponent from "../psignalscomp/SignalsComp";
import {ReactComponent as HandIconWhite} from "../../images/hand_white.svg";

class Caliberation extends Component {
  constructor(props) {
    super(props);
    this.signalComponentRef = React.createRef();
  }

  startTraining = () => {
    const {ipcRenderer} = window.require("electron");
    ipcRenderer.send("socket_data_send", "stop_raw_real_time_data");
    this.props.callbackSetMainSection("user_training");
  };

  componentDidMount = () => {
    console.log("Caliberation Component Mounted");
    const {ipcRenderer} = window.require("electron");
    ipcRenderer.send("socket_data_send", "start_raw_real_time_data");

    ipcRenderer.on(
      "socket_data_received",
      function(event, data) {
        try {
          // console.log(String(data), " at ", new Date().getTime());
          // console.log(String(data), "New Data at ", new Date().getTime());
          var jsonObject = JSON.parse(String(data));
          if (jsonObject != null && jsonObject.type == "real_time_raw_data") {
            this.signalComponentRef.addPoints(jsonObject);
          } else if (jsonObject != null && jsonObject.type == "start_training_success") {
            this.props.callbackSetMainSection("user_training");
          }
        } catch (e) {
          console.log("Error in paring data ", String(data));
          console.log(e);
        }
      }.bind(this)
    );
  };

  componentWillUnmount = () => {
    console.log("Caliberation Component Unmounted!!");
    const {ipcRenderer} = window.require("electron");
    ipcRenderer.send("socket_data_send", "stop_raw_real_time_data");
    ipcRenderer.removeAllListeners("socket_data_received");
  };

  render() {
    const {classes} = this.props;
    return (
      <div style={{height: "100%", width: "100%"}}>
        <div style={{display: "flex", flexDirection: "column", justifyContent: "start", height: "100%", padding: "2%"}}>
          <div style={{display: "flex", justifyContent: "flex-start", flexDirection: "column"}}>
            <SignalComponent onRef={(ref) => (this.signalComponentRef = ref)} parentComponentName={"caliberation"} />
          </div>

          <div style={{display: "flex", justifyContent: "center", paddingTop: 30}}>
            <Fab variant="extended" color="primary" aria-label="Add" onClick={this.startTraining} className={classes.margin}>
              <HandIconWhite className={classes.extendedIcon} />
              Next Step ( Click Training )
            </Fab>
          </div>
        </div>
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

export default withStyles(styles, {withTheme: true})(Caliberation);
