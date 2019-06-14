import PropTypes from "prop-types";
import React from "react";
import { graphql } from "gatsby";
import { ThemeContext } from "../layouts";
import Article from "../components/Article";
import Contact from "../components/Contact";
import Headline from "../components/Article/Headline";
import Seo from "../components/Seo";
import contactImg from "../images/png/contact.png";

const ContactPage = props => {
  return (
    <React.Fragment>
      <ThemeContext.Consumer>
        {theme => (
          <Article theme={theme}>
            <img src={contactImg} style={{ "padding-top": "0%", "padding-right": "0%" }} />
            <div
              style={{
                "font-style": "italic",
                color: "#514f4d",
                "padding-bottom": "30px",
                "padding-left": "63px"
              }}
            >
              Nous serons ravis de répondre à vos questions et suggestions
            </div>
            <Contact theme={theme} />
          </Article>
        )}
      </ThemeContext.Consumer>
    </React.Fragment>
  );
};

ContactPage.propTypes = {
  data: PropTypes.object.isRequired
};

export default ContactPage;

//eslint-disable-next-line no-undef
export const query = graphql`
  query ContactQuery {
    site {
      siteMetadata {
        facebook {
          appId
        }
      }
    }
  }
`;
