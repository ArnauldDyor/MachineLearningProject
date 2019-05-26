import React from 'react';
import frFlag from '../resultImages/fr.jpg';
import usaFlag from '../resultImages/usa.jpg';
import unknownFlag from '../resultImages/unknown.png';
import loading from '../loading.gif';

export class Resultbox extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            isHidden: true,
            flag: null,
            phrase: null,
            width: '120px',
            height: '100px'
        };
        window.myComponent = this;
    }

    toggleHidden() {
        this.setState({
            isHidden: !this.state.isHidden
        })
    }

    hide() {
        this.setState({
            isHidden: true
        })
    }

    changeFlag(flag) {
        if (this.state.isHidden) {
            this.toggleHidden();
        }

        let phrase;

        if (flag === 'frFlag') {
            flag = frFlag;
            phrase = 'This is the French flag !'
        }
        else if (flag === 'usaFlag') {
            flag = usaFlag;
            phrase = 'This is the American flag'
        }
        else if (flag === 'unknownFlag') {
            flag = unknownFlag;
            phrase = 'An error occured, your connnection or the server may be down !'
        }
        else if (flag === 'loading') {
            flag = loading;
            phrase = 'Loading...'
            this.setState({
                flag: flag,
                phrase: phrase,
                width: '160px',
                height: '20px'
            })
            return;
        }

        this.setState({
            flag: flag,
            phrase: phrase,
            width: '120px',
            height: '100px'
        })
    }

    getVisibility() {
        return this.state.isHidden;
    }

    render() {

        return <div className="resultBox">
            {!this.state.isHidden &&
                <div><img className="resultImage" src={this.state.flag} alt="" width={this.state.width} height={this.state.height} />
                    <div> {this.state.phrase} </div>
                </div>
            }
        </div>;
    }
}