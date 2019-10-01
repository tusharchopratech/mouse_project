import React, { Component } from "react";
import { withStyles } from "@material-ui/core/styles";

class Report extends Component {
  constructor(props) {
    super(props);
    this.report = JSON.stringify(this.props.report, null, 2);
    console.log(this.props.report);
    this.state = {
      truePositives: 0.0,
      falsePositives: 0.0,
      averageLead: 0.0
    };
  }

  componentDidMount = () => {
    if (this.props.report != null) {
      this.setState({
        truePositives: this.props.report.true_positives,
        falsePositives: this.props.report.false_positives,
        averageLead: this.props.report.average_lead
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
        <div>True Positives : {this.state.truePositives}</div>
        <div>False Positives : {this.state.falsePositives}</div>
        <div>Average Lead : {this.state.averageLead}</div>
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
