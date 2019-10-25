import React, { Component } from "react";
import { withStyles } from "@material-ui/core/styles";

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

  componentDidMount = () => {
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
    return (
      <div>
        {/* <div>
          Actual Left Click Indices :
          <pre>{JSON.stringify(this.props.report.actual_left_click_indices)}</pre>
        </div>
        <div>
          Actual Right Click Indices :
          <pre>{JSON.stringify(this.props.report.actual_right_click_indices)}</pre>
        </div>
        <div>
          For {this.props.report.results[0].algo_type} :
         <pre>Impulse Left Click : {JSON.stringify(this.props.report.results[0].left_click)}<br />Impulse Right Click :{JSON.stringify(this.props.report.results[0].right_click)}</pre>
        </div>
        <div>
          For {this.props.report.results[1].algo_type} :
         <pre>Impulse Left Click : {JSON.stringify(this.props.report.results[1].left_click)}<br />Impulse Right Click :{JSON.stringify(this.props.report.results[1].right_click)}</pre>
        </div>
        <div>
          For {this.props.report.results[2].algo_type} :
         <pre>Impulse Left Click : {JSON.stringify(this.props.report.results[2].left_click)}<br />Impulse Right Click :{JSON.stringify(this.props.report.results[2].right_click)}</pre>
        </div>
        <div>
          For {this.props.report.results[3].algo_type} :
         <pre>Impulse Left Click : {JSON.stringify(this.props.report.results[3].left_click)}<br />Impulse Right Click :{JSON.stringify(this.props.report.results[3].right_click)}</pre>
        </div> */}
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
    );
  }
}

const styles = theme => ({
  margin: {
    margin: theme.spacing.unit
  },
  extendedIcon: {
    marginRight: theme.spacing.unit
  }
});

export default withStyles(styles, { withTheme: true })(Report);
