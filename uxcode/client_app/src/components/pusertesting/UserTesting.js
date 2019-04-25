import React, { Component } from 'react'
import PropTypes from 'prop-types'

export default class UserTesting extends Component {
  static propTypes = {
    prop: PropTypes
  }

  render() {
    return (
      <div>
         <p>User Testing Section</p>
      </div>
    )
  }
}
