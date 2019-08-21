import React, { Component } from 'react';
import { withStyles } from '@material-ui/core/styles';
import Fab from '@material-ui/core/Fab';
import ReactDOM from 'react-dom';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';
import { ReactComponent as MouseIcon } from '../../images/mouse_white.svg';
import CircularProgress from '@material-ui/core/CircularProgress';

class Caliberation extends Component {

  constructor(props) {
    super(props)
    this.left = this.props.myLeft + 50; // adding 50 for bounday offset
    this.right = this.props.myRight - 120; // bounday offset including width of the button
    this.top = this.props.myTop + 64 + 50; // adding 64 for toolbar, 50 for boundary off set
    this.bottom = this.props.myBottom - 80; // boundary offset including height of the button
    this.clickSequence = [];

    this.currentClickType = 'left';
    this.leftClickId = 0;
    this.rightClickId = 2;
    this.thumb1ClickId = 3;
    this.thumb2ClickId = 4;

    this.i = 0;
    this.click_info = {
      up: null,
      down: null
    };
    this.clicksInfoArray = []
    this.state = {
      start_showing_random_clicks: false,
      openFinishDialog: false,
      openLoadingDialogForUserTraining: false,
    };
  };

  getNextClickType = () => {
    var rand = Math.floor(Math.random() * 3);
    if (rand == 0) {
      return "left";
    } else if (rand == 1) {
      return "right";
    } else if (rand == 2) {
      return "thumb";
    }
  }

  renderTest = (val) => {
    if (val === true) {
      console.log("I run ", this.i);
      if (this.i < this.clickSequence.length) {
        this.currentClickType = this.clickSequence[this.i];
        this.i++;
        this.x = this.top + Math.random() * (this.bottom - this.top);
        this.y = this.left + Math.random() * (this.right - this.left);
        return <Fab
          size="small"
          variant="extended"
          color="primary"
          aria-label="Add"
          ref="test_click_button"
          style={{ position: 'absolute', top: this.x, left: this.y }}
          onMouseDown={this.onMouseDown.bind(this)}> Click {this.currentClickType}!</Fab>
      } else {
        console.log("Done Test");
        this.setState({
          start_showing_random_clicks: false,
          showCaliberationButton: false,
          openFinishDialog: false,
          openLoadingDialogForUserTraining: true
        });
        const { ipcRenderer } = window.require("electron");
        ipcRenderer.send("socket_data_send", "stop_training");
      }
    } else {
      return;
    }
  };

  onClickStartTraining = (event) => {
    if (window.require('electron').remote.getGlobal('shared_object').current_envirnoment == "dev") {
      this.setState({
        start_showing_random_clicks: false,
        showCaliberationButton: false,
        openFinishDialog: false,
        openLoadingDialogForUserTraining: true
      });
      const { ipcRenderer } = window.require("electron");
      ipcRenderer.send("socket_data_send", "stop_training");
    } else {
      ReactDOM.findDOMNode(this.refs.start_caliberation_button).style.display = 'none';
      setTimeout(function () {
        this.setState({
          start_showing_random_clicks: true,
          openFinishDialog: false
        });
      }.bind(this), 2000);
    }
  }

  onMouseDown = (event) => {
    console.log(event.button)

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
      start_showing_random_clicks: true,
      openFinishDialog: false
    });

    if (ReactDOM.findDOMNode(this.refs.test_click_button) != null) {
      ReactDOM.findDOMNode(this.refs.test_click_button).style.display = 'none';
    }

    setTimeout(function () {
      if (ReactDOM.findDOMNode(this.refs.test_click_button) != null) {
        ReactDOM.findDOMNode(this.refs.test_click_button).style.display = '';
      }
    }.bind(this), 2000);

  };

  closeFinishDialog = () => {
    this.setState({
      start_showing_random_clicks: false,
      showCaliberationButton: false,
      openFinishDialog: false
    });
  };

  componentDidMount = () => {
    for (var i = 0; i < 5; i++) { this.clickSequence.push("left"); }
    for (var i = 0; i < 5; i++) { this.clickSequence.push("right"); }
    for (var i = 0; i < 5; i++) { this.clickSequence.push("thumb"); }
    this.clickSequence = this.shuffleArray(this.clickSequence);

    const { ipcRenderer } = window.require("electron");
    ipcRenderer.on('socket_data_received', function (event, data) {
      var jsonObject = JSON.parse(String(data));
      if (jsonObject.type == "algo_outputs") {
        // console.log(jsonObject);
        this.setState({
          start_showing_random_clicks: false,
          showCaliberationButton: false,
          openFinishDialog: false,
          openLoadingDialogForUserTraining: false
        });
        this.props.callbackSetMainSection('report',jsonObject);
      }
    }.bind(this));
  }

  shuffleArray = (arra1) => {
    var ctr = arra1.length, temp, index;
    while (ctr > 0) {
      index = Math.floor(Math.random() * ctr);
      ctr--;
      temp = arra1[ctr];
      arra1[ctr] = arra1[index];
      arra1[index] = temp;
    }
    return arra1;
  }

  render() {
    const { classes } = this.props;
    return (
      <div>
        {/* <p>Caliberation Section</p> */}
        <Fab
          variant="extended"
          color="primary"
          aria-label="Add"
          ref="start_caliberation_button"
          onMouseDown={this.onClickStartTraining.bind(this)}
          className={classes.margin}
        >
          <MouseIcon className={classes.extendedIcon} />
          Start Training
        </Fab>
        {this.renderTest(this.state.start_showing_random_clicks)}

        <Dialog
          open={this.state.openFinishDialog}
          onClose={this.closeFinishDialog}
          aria-labelledby="alert-dialog-title"
          aria-describedby="alert-dialog-description"
          disableBackdropClick={true}
          disableEscapeKeyDown={true}
        >
          <DialogTitle id="alert-dialog-title">{"Caliberation Finished"}</DialogTitle>
          <DialogContent>
            <DialogContentText id="alert-dialog-description">
              Thank you. Please check C/impulse_data for results.
            </DialogContentText>
          </DialogContent>
          <DialogActions>
            <Button onClick={this.closeFinishDialog} color="primary">
              Next
            </Button>
          </DialogActions>
        </Dialog>

        <Dialog
          open={this.state.openLoadingDialogForUserTraining}
          aria-labelledby="alert-dialog-title"
          aria-describedby="alert-dialog-description"
          disableBackdropClick={true}
          disableEscapeKeyDown={true}
        >
          <DialogTitle id="alert-dialog-title">{"Extracting Information..."}</DialogTitle>
          <DialogContent>
            <CircularProgress className={classes.progress} />
          </DialogContent>
        </Dialog>
      </div>
    )
  }
}

const styles = theme => ({
  margin: {
    margin: theme.spacing.unit,
  },
  extendedIcon: {
    marginRight: theme.spacing.unit,
  },
});

export default withStyles(styles, { withTheme: true })(Caliberation);
