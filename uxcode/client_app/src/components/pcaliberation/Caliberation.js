
import React, { Component } from 'react';
import { withStyles } from '@material-ui/core/styles';
import Fab from '@material-ui/core/Fab';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';
import { ReactComponent as MouseIcon } from '../../images/mouse_white.svg';
const BrowserWindow = window.require('electron').remote.BrowserWindow;

class Caliberation extends Component {

  constructor(props) {
    super(props)
    this.left = this.props.myLeft + 50; // adding 50 for bounday offset
    this.right = this.props.myRight - 120; // bounday offset including width of the button
    this.top = this.props.myTop + 64 + 50; // adding 64 for toolbar, 50 for boundary off set
    this.bottom = this.props.myBottom - 80; // boundary offset including height of the button
    this.max_clicks = 5;
    this.i = 0;
    this.click_info = {
      up: null,
      down: null
    };
    this.clicksInfoArray = []
    this.state = {
      start_showing_random_clicks: false,
      showCaliberationButton: true,
      openFinishDialog: false
    };
  };

  renderTest = (val) => {
    if (val === true) {
      if (this.i < this.max_clicks) {
        this.i++;
        this.x = this.top + Math.random() * (this.bottom - this.top);
        this.y = this.left + Math.random() * (this.right - this.left);
        return <Fab
          size="small"
          variant="extended"
          color="primary"
          aria-label="Add"
          style={{ position: 'absolute', top: this.x, left: this.y }}
          onMouseDown={this.onMouseDown}
          onMouseUp={this.onMouseUp}
          onClick={this.startCaliberation}> Click Me!</Fab>
      } else {
        console.log("Done Test");
        this.setState({
          start_showing_random_clicks: false,
          showCaliberationButton: false,
          openFinishDialog: true
        });
      }
    } else {
      return;
    }
  };

  onMouseDown = () => {
    this.click_info.down = new Date().toUTCString();
  };

  onMouseUp = () => {
    this.click_info.up = new Date().toUTCString();
    this.clicksInfoArray.push(this.click_info);
  };

  startCaliberation = () => {
    this.setState({
      start_showing_random_clicks: true,
      showCaliberationButton: false,
      openFinishDialog: false
    });
    // let w = new BrowserWindow({ 
    //   width: 120, 
    //   height: 60,
    //   x:0,
    //   y:0,
    //   title:"Widget",
    //   resizable: false,
    //   fullscreenable:false,
    //   // frame: false,
    //   alwaysOnTop:true 
    // })

  };

  closeFinishDialog = () => {
    this.setState({
      start_showing_random_clicks: false,
      showCaliberationButton: false,
      openFinishDialog: false
    });
  };

  render() {
    const { classes } = this.props;
    return (
      <div>
        {/* <p>Caliberation Section</p> */}
        <Fab
          variant="extended"
          color="primary"
          aria-label="Add"
          onClick={this.startCaliberation}
          style={{ display: this.state.showCaliberationButton ? '' : 'none' }}
          className={classes.margin}
        >
          <MouseIcon className={classes.extendedIcon} />
          Start Caliberation
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
              Thank you for the calibration. Your click timings have been saved and threshold has been set.
            </DialogContentText>
          </DialogContent>
          <DialogActions>
            <Button onClick={this.closeFinishDialog} color="primary" autoFocus>
              Next
            </Button>
          </DialogActions>
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
