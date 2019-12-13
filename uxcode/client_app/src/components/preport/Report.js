import React, {Component} from "react";
import {withStyles} from "@material-ui/core/styles";
import {ReactComponent as GamePadIconWhite} from "../../images/gamepad_white.svg";
import Fab from "@material-ui/core/Fab";
import * as Constants from '../edata/Constants';

class Report extends Component {
  constructor(props) {
    super(props);
    this.report = JSON.stringify(this.props.report, null, 2);
    console.log(this.props.report);
    this.state = {
      leftTruePositives: 0.0,
      leftFalsePositives: 0.0,
      leftAverageLead: 0.0,
      rightTruePositives: 0.0,
      rightFalsePositives: 0.0,
      rightAverageLead: 0.0
    };
  }

  startRealTimePlay = () => {
    this.props.callbackSetMainSection("real_time_data");
  };

  componentDidMount = () => {
    Constants.setCurrentState(Constants.CURRENT_IMPULSE_STATE.SCREEN_REPORT);
    if (this.props.report != null) {
      this.setState({
        leftTruePositives: this.props.report.left_click.true_positives,
        leftFalsePositives: this.props.report.left_click.false_positives,
        leftAverageLead: this.props.report.left_click.average_lead,
        rightTruePositives: this.props.report.right_click.true_positives,
        rightFalsePositives: this.props.report.right_click.false_positives,
        rightAverageLead: this.props.report.right_click.average_lead
      });
    }
  };

  render() {
    const {classes} = this.props;
    return (
      <div>
        <div style={{display: "flex", flexDirection: "column", width: "100%", alignItems: "center"}}>
          <h5>For Left Click</h5>
          <div>True Positives : {this.state.leftTruePositives}</div>
          <div>False Positives : {this.state.leftFalsePositives}</div>
          <div>Average Lead : {this.state.leftAverageLead}</div>
          <br></br>
          <h5>For Right Click</h5>
          <div>True Positives : {this.state.rightTruePositives}</div>
          <div>False Positives : {this.state.rightFalsePositives}</div>
          <div>Average Lead : {this.state.rightAverageLead}</div>
        </div>
        <br></br>
        <Fab variant="extended" color="primary" aria-label="Add" onClick={this.startRealTimePlay} className={classes.margin}>
          <GamePadIconWhite className={classes.extendedIcon} />
          {"Start Real Time Play"}
        </Fab>
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

export default withStyles(styles, {withTheme: true})(Report);
