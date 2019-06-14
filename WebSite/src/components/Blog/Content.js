import Trombi from "../../pages/trombi";
import PropTypes from "prop-types";
import React from "react";

const Content = props => {
  return (
    <React.Fragment>
      <Trombi />
    </React.Fragment>
  );
};

Content.propTypes = {
  page: PropTypes.object.isRequired
};

export default Content;
