import React, { Component } from 'react'
import ListItem from '@material-ui/core/ListItem';
import ListItemIcon from '@material-ui/core/ListItemIcon';
import ListItemText from '@material-ui/core/ListItemText';
import { withStyles } from '@material-ui/core/styles';
import Drawer from '@material-ui/core/Drawer';
import List from '@material-ui/core/List';
import { ReactComponent as WaveIcon } from '../../images/wave.svg';
import { ReactComponent as MouseIcon } from '../../images/mouse.svg';
import { ReactComponent as GamePadIcon } from '../../images/gamepad.svg';
import { ReactComponent as DocumentIcon } from '../../images/document.svg';


const drawerWidth = 240;
const styles = theme => ({
    drawer: {
        width: drawerWidth,
        flexShrink: 0,
    },
    drawerPaper: {
        width: drawerWidth,
    },
    toolbar: theme.mixins.toolbar,
});


class MyDrawer extends Component {

    constructor(props) {
        super(props)
        this.state = {
        };
    };

    handleClick = (val) => {
     this.props.callbackSetMainSection(val);
    };

    render() {
        const { classes } = this.props;
        return (
            <Drawer
                className={classes.drawer}
                variant="permanent"
                classes={{
                    paper: classes.drawerPaper,
                }}
            >
                <div className={classes.toolbar} />
                <List>
                    <ListItem button onClick={this.handleClick.bind(this,'caliberation')}>
                        <ListItemIcon>
                            <WaveIcon />
                        </ListItemIcon>
                        <ListItemText primary={'Caliberation'} />
                    </ListItem>
                    <ListItem button onClick={this.handleClick.bind(this,'user_training')}>
                        <ListItemIcon>
                            <MouseIcon />
                        </ListItemIcon>
                        <ListItemText primary={'User Traning'} />
                    </ListItem>
                    <ListItem button onClick={this.handleClick.bind(this,'real_time_data')}>
                        <ListItemIcon>
                            <GamePadIcon />
                        </ListItemIcon>
                        <ListItemText primary={'Real Time Data'} />
                    </ListItem>
                    <ListItem button onClick={this.handleClick.bind(this,'report')}>
                        <ListItemIcon>
                            <DocumentIcon />
                        </ListItemIcon>
                        <ListItemText primary={'Report'} />
                    </ListItem>
                </List>
            </Drawer>
        )
    }
}

export default withStyles(styles, { withTheme: true })(MyDrawer);