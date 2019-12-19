import React, {Component} from "react";
import ListItem from "@material-ui/core/ListItem";
import ListItemIcon from "@material-ui/core/ListItemIcon";
import ListItemText from "@material-ui/core/ListItemText";
import {withStyles} from "@material-ui/core/styles";
import Drawer from "@material-ui/core/Drawer";
import List from "@material-ui/core/List";
import {ReactComponent as WaveIcon} from "../../images/wave.svg";
import {ReactComponent as MouseIcon} from "../../images/mouse.svg";
import {ReactComponent as GamePadIcon} from "../../images/gamepad.svg";
import {ReactComponent as DocumentIcon} from "../../images/document.svg";
import {ReactComponent as HandIcon} from "../../images/hand.svg";
import * as Constants from "../edata/Constants";
import Snackbar from "@material-ui/core/Snackbar";




class MyDrawer extends Component {
  constructor(props) {
    super(props);
    this.state = {};
  }

  handleClick = (val) => {
    if (Constants.getCurrentState() == Constants.CURRENT_IMPULSE_STATE.RUNNING_USER_TRAINING) {
      this.setState({drawerSnackbarErrorMessage: "Please complete the training session first.", openSnackBarDrawer: true});
      setTimeout(
        function() {
          this.setState({openSnackBarDrawer: false});
        }.bind(this),
        4000
      );
    } else if (Constants.getCurrentState() == Constants.CURRENT_IMPULSE_STATE.RUNNING_REAL_TIME) {
      this.setState({drawerSnackbarErrorMessage: "Please stop Real Time Play first.", openSnackBarDrawer: true});
      setTimeout(
        function() {
          this.setState({openSnackBarDrawer: false});
        }.bind(this),
        4000
      );
    } else {
      this.props.callbackSetMainSection(val);
    }
  };

  render() {
    const {classes} = this.props;
    return (
      <div>
        <Drawer
          className={classes.drawer}
          variant="permanent"
          classes={{
            paper: classes.drawerPaper
          }}>
          <div className={classes.toolbar} />
          <List>
            <ListItem button onClick={this.handleClick.bind(this, "welcome")}>
              <ListItemIcon>
                <HandIcon />
              </ListItemIcon>
              <ListItemText primary={"Welcome"} />
            </ListItem>
            <ListItem button onClick={this.handleClick.bind(this, "caliberation")}>
              <ListItemIcon>
                <WaveIcon />
              </ListItemIcon>
              <ListItemText primary={"Caliberation"} />
            </ListItem>
            <ListItem button onClick={this.handleClick.bind(this, "user_training")}>
              <ListItemIcon>
                <MouseIcon />
              </ListItemIcon>
              <ListItemText primary={"User Training"} />
            </ListItem>
            <ListItem button onClick={this.handleClick.bind(this, "report")}>
              <ListItemIcon>
                <DocumentIcon />
              </ListItemIcon>
              <ListItemText primary={"Report"} />
            </ListItem>
            <ListItem button onClick={this.handleClick.bind(this, "real_time_data")}>
              <ListItemIcon>
                <GamePadIcon />
              </ListItemIcon>
              <ListItemText primary={"Real Time Play"} />
            </ListItem>
          </List>
        </Drawer>
        <Snackbar
          // key={messageInfo ? messageInfo.key : undefined}
          anchorOrigin={{
            vertical: "bottom",
            horizontal: "left"
          }}
          open={this.state.openSnackBarDrawer}
          ContentProps={{
            "aria-describedby": "message-id"
          }}
          message={<span id="message-id">{this.state.drawerSnackbarErrorMessage}</span>}
        />
      </div>
    );
  }
}

const drawerWidth = 240;
const styles = (theme) => ({
  drawer: {
    width: drawerWidth,
    flexShrink: 0
  },
  drawerPaper: {
    width: drawerWidth,
    background: "#ffffff"
  },
  toolbar: theme.mixins.toolbar
});


export default withStyles(styles, {withTheme: true})(MyDrawer);
