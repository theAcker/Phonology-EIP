import PropTypes from "prop-types";
import React from "react";
import Form from "antd/lib/form";
import Input from "antd/lib/input";
import Button from "antd/lib/button";
const FormItem = Form.Item;
const { TextArea } = Input;
import "antd/lib/form/style/index.css";
import "antd/lib/input/style/index.css";
import "antd/lib/button/style/index.css";
import { ThemeContext } from "../layouts";
import acker from "../images/png/acker_a (1).png";
import allary from "../images/png/alexandre.allary (1).png";
import tachet from "../images/png/benoit.tachet (1).png";
import polar from "../images/png/charles.polart (1).png";
import dinh from "../images/png/dinh_d (1).png";
import larriv from "../images/png/larriv_a.png";
import young from "../images/png/paul.young.png";
import adonias from "../images/png/yves.adonias.png";
import ourTeam from "../images/png/OurTeam.png";

const TeamPage = props => {
  return (
    <React.Fragment>
      <div style={{ width: "100%", "padding-bottom": "2%" }}>
        <img src={ourTeam} style={{ "padding-top": "3%", "padding-left": "35%" }} />
      </div>
      <div class="row">
        <img src={acker} style={{ "padding-top": "3%", "padding-left": "5%" }} />
        <img src={tachet} style={{ "padding-top": "3%", "padding-left": "10%" }} />
        <img src={polar} style={{ "padding-top": "3%", "padding-left": "10%" }} />
        <img src={dinh} style={{ "padding-top": "3%", "padding-left": "10%" }} />
      </div>
      <div style={{ "padding-left": "8%", color: "#2b2826" }}>
        <h4 style={{ "padding-left": "0%", color: "#2b2826", display: "inline-block" }}>
          Alexandre Acker
        </h4>
        <h4 style={{ "padding-left": "17%", color: "#2b2826", display: "inline-block" }}>
          Benoit Tachet
        </h4>
        <h4 style={{ "padding-left": "19%", color: "#2b2826", display: "inline-block" }}>
          Charles Polart
        </h4>
        <h4 style={{ "padding-left": "19%", color: "#2b2826", display: "inline-block" }}>
          Dylan Dinh
        </h4>
      </div>
      <div class="row">
        <img src={allary} style={{ "padding-top": "0%", "padding-left": "5%" }} />
        <img src={larriv} style={{ "padding-top": "3%", "padding-left": "10%" }} />
        <img src={young} style={{ "padding-top": "3%", "padding-left": "10%" }} />
        <img src={adonias} style={{ "padding-top": "3%", "padding-left": "10%" }} />
      </div>
      <div style={{ "padding-left": "8%", color: "#2b2826", "padding-bottom": "15%" }}>
        <h4 style={{ "padding-left": "0%", color: "#2b2826", display: "inline-block" }}>
          Alexandre Allary
        </h4>
        <h4 style={{ "padding-left": "17%", color: "#2b2826", display: "inline-block" }}>
          Auguste Larrive
        </h4>
        <h4 style={{ "padding-left": "19%", color: "#2b2826", display: "inline-block" }}>
          Paul Young
        </h4>
        <h4 style={{ "padding-left": "19%", color: "#2b2826", display: "inline-block" }}>
          Yves Adonias
        </h4>
      </div>
    </React.Fragment>
  );
};

TeamPage.propTypes = {
  data: PropTypes.object.isRequired
};

export default TeamPage;
