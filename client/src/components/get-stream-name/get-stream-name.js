import React, { Component } from "react";
import Errors from '../errors/errors';


export default class GetStreamName extends Component {
    constructor(props) {
        super(props);
        this.state = {
            streamName: '',
            url: '',
            errors: '',
            response: ''
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
        this.CallGetStreamName();
    }

    renderErrors() {
        return (
            <div>
                <Errors errors={this.state.errors} />
            </div>
        );
    }

    async CallGetStreamName() {
        try {
            const requestOptions = {
                method: 'GET',
            };

            const response = await fetch(`http://localhost:3001/stream/${this.state.name}`, requestOptions);
            this.setState({
                response: response
            });
        }
        catch (ex) {
            this.setState({
                response: ex.message
            });
        }
    }

    render() {
        return (
            <div>
                <form onSubmit={this.handleSubmit} >
                    <div className="form-group">
                        <label for="nameImput">[GET /Stream:name] Name</label>
                        <input type="text" name="streamName" value={this.state.streamName} onChange={this.handleChange} className="form-control" id="nameImput" placeholder="Stream Name" />
                    </div>
                    <input type="submit" value="Submit" className="btn btn-primary" />
                </form>
                <p>{this.state.response}</p>
            </div>
        )
    }
}
