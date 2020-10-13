import React from 'react';
import logo from './logo.svg';
import './App.css';
import PostStream from './components/post-stream/post-stream'
import GetStreamName from './components/get-stream-name/get-stream-name'

function App() {
  return (
    <div className="App">
      <PostStream />
      <GetStreamName />
    </div>
  );
}

export default App;
