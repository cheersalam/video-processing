import React, { Component } from "react";
import Errors from '../errors/errors';


export default class PostStream extends Component {
    constructor(props) {
        super(props);
        this.state = {
            streamName: '',
            url: '',
            errors: ''
        };

        this.handleChange = this.handleInputChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleInputChange(event) {
        const target = event.target;
        const value = target.type === 'checkbox' ? target.checked : target.value;
        const name = target.name;

        this.setState({
            [name]: value
        });
        console.log('Change detected. State updated' + name + ' = ' + value);
    }

    handleSubmit(event) {
        console.log('A form was submitted: ' + this.state.streamName + ' // ' + this.state.url);
        event.preventDefault();
        this.PostStream();
    }

    renderErrors() {
        return (
            <div>
                <Errors errors={this.state.errors} />
            </div>
        );
    }

    async PostStream() {
        const requestOptions = {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ streamName: this.state.streamName, url: this.state.url })
        };
        const response = await fetch('http://localhost:3001/stream', requestOptions);
       // this.setState({
       //     parseErrors: [...this.state.parseErrors, errorMsg]
       // });

        console.log(response);
        const data = await response.json();
    }

    render() {
        return (
            <div>
                <form onSubmit={this.handleSubmit} >
                    <div className="form-group">
                        <label for="nameImput">Stream Name</label>
                        <input type="text" name="streamName" value={this.state.streamName} onChange={this.handleChange} className="form-control" id="nameImput" placeholder="Stream Name" />
                    </div>
                    <div className="form-group">
                        <label for="emailImput">URL</label>
                        <input name="url" type="text" value={this.state.url} onChange={this.handleChange} className="form-control" id="emailImput" placeholder="URL" />
                    </div>
                    <input type="submit" value="Submit" className="btn btn-primary" />
                </form>
            </div>
        )
    }
}
