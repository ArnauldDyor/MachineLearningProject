import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import 'react-dropzone-uploader/dist/styles.css'
import Dropzone from 'react-dropzone-uploader'
import { Resultbox } from '../src/component/result_box';


class App extends Component {

  render() {

    const UploadPic = () => {

      const handleSubmit = (files, allFiles) => {
        allFiles.forEach(f => f.remove())
        window.myComponent.hide();
      }

      const getUploadParams = () => {
        window.myComponent.changeFlag('loading');
        return { url: 'http://localhost:3000/submit' }
      }

      return (
        <Dropzone
          getUploadParams={getUploadParams}
          onSubmit={handleSubmit}
          maxFiles={1}
          submitButtonContent={"Clear and upload a new image"}
          submitButtonDisabled={files => files.length < 1}
          accept="image/*"
          inputContent={(files, extra) => (extra.reject ? 'Image files only' : 'Drag n\' drop an image ! ')}
          styles={{
            dropzoneReject: { borderColor: 'red', backgroundColor: '#DAA' },
            inputLabel: (files, extra) => (extra.reject ? { color: 'red' } : {}),
          }}
        />
      )
    }
    let accessNumber = 0;
    XMLHttpRequest.prototype._originalOpen = XMLHttpRequest.prototype.open;
    XMLHttpRequest.prototype.open = function (method, url, async, user, password) {
      this._originalOpen(method, url, async, user, password);
      const response = this;
      accessNumber++;
      let loop = 0;
      var intervalTimer = setInterval(checkResponse, 40);
      function checkResponse() {

        loop++;

        if (accessNumber === 1) {
          clearInterval(intervalTimer);
          loop = 0;
          return;
        }

        if (loop > 125 && accessNumber > 1) {
          window.myComponent.changeFlag('unknownFlag');
          clearInterval(intervalTimer);
          loop = 0;
          return;
        }
        if (response.readyState === 4) {
          if (response.responseText === 'frFlag') {
            window.myComponent.changeFlag('frFlag');
            clearInterval(intervalTimer);
            loop = 0;
            return;
          }
          else if (response.responseText === 'usaFlag') {
            window.myComponent.changeFlag('usaFlag');
            clearInterval(intervalTimer);
            loop = 0;
            return;
          }
          else if(response.status !== 200){
            window.myComponent.changeFlag('unknownFlag');
            clearInterval(intervalTimer);
            loop = 0;
            return;
          }
        }
      };

    }

    return (

      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Annual project machine learning</h2>
          <h2>Flag recognition</h2>
        </div>
        <div className="dz-container">
          <UploadPic />
        </div>
        <Resultbox />
      </div>

    );
  }
}

export default App;
