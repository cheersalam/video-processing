import React, { Component } from "react";
//import './errors.css'

export default class Errors extends Component {
    constructor(props) {
        super(props);
        this.state = { errors: "" };
    }

    render() {
        const errors = this.props.errors || [];
        return (
            <section>
                {errors.map((e, i) => (
                    <section className="error" key={i}>
                        {" "}
                        {e}
                    </section>
                ))}
            </section>
        );
    }
}
