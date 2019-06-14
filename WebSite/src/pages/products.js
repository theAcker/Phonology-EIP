import React from "react";
import ContactPage from "./contact";
import TeamPage from "./team";
import ourProject from "../images/png/ourProject.png";

const Products = () => {
  return (
    <React.Fragment>
      <section id="project">
        <div style={{ width: "100%", "padding-bottom": "2%", "background-color": "#fafaf9" }}>
          <img src={ourProject} style={{ "padding-top": "3%", "padding-left": "35%" }} />
          <div style={{ width: "100%", "padding-top": "4%" }}>
            <h1
              style={{
                "padding-left": "37%",
                color: "#212529",
                "font-family": "Georgia, serif;"
              }}
            >
              Un logiciel d'ortophonie portable
            </h1>
            <div style={{ width: "100%", "padding-top": "4%" }}>
              <span
                style={{
                  "padding-left": "22%",
                  color: "#212529",
                  "font-family": "Georgia, serif;"
                }}
              >
                VoiceWatcher est un puissant outil de langage et de parole qui transforme les mots
                et les sons parlés en graphiques imaginatifs.
              </span>
            </div>
            <div style={{ width: "100%", "padding-top": "1%", "padding-bottom": "20%" }}>
              <span
                style={{
                  "padding-left": "25%",
                  color: "#212529",
                  "font-family": "Georgia, serif;"
                }}
              >
                C'est un logiciel conçu et adapté pour les personnes souffrant de troubles de la
                paroles, du langage ou de l'audition.
              </span>
            </div>
          </div>
        </div>
      </section>
      {/*      <section id="about">
        <h1 className="headertekst">Equipes</h1>
        <img src={A} />
        <img src={B} />
        <img src={C} />
        <img src={D} />
        <img src={E} />
        <img src={F} />
        <img src={G} />
        <img src={H} />
      </section>*/}
      <section id="team">
        <TeamPage />
      </section>
      <section id="contact">
        <ContactPage />
      </section>
      {/* --- STYLES --- */}
      <style jsx>{`
        div {
          list-style: none;
          margin: 0 auto;
        }

        main {
          border-width: thin;
          background-image: linear-gradient(
            to right,
            rgb(70, 130, 180),
            rgb(0, 139, 139),
            rgb(240, 230, 140),
            rgb(255, 140, 0),
            rgb(220, 20, 60)
          );
        }

        h1 {
          color: grey;
        }

        h1.headertekst {
          text-align: center;
          color: black;
        }
      `}</style>
    </React.Fragment>
  );
};

export default Products;
