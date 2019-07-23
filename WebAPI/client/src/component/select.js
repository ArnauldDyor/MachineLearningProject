import React from 'react';

export class Select extends React.Component {
    constructor(props) {
      super(props);
      this.state = {
        items: ['Choose a value', 'Rosenblatt', 'Multilayer Perceptron', 'RBF']
      };
    }
  
    onSelect = e => {
        fetch('http://localhost:3000/function', {
            method: 'POST',
            headers: {
              'Accept': 'application/json',
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({
              function: e.target.value
            })
          })
          
    }
  
    render() {
      const{items} = this.state;
      return (
        <div>
          <select onChange={this.onSelect}>
          {
            items.map(item => {
              return (<option key={item} value={item}>{item}</option>)
            })
          }
          </select>
        </div>
      );
    }
  }